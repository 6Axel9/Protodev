#include "Protodev.h"
#include "Avatar.h"
#include "PickupItem.h"
#include "Laser.h"
#include "Monster.h"
#include "Bullet.h"
#include "GUI.h"
#include "ObjectivesComponent.h"
#include "Objective.h"

//========================================== Constructor
AAvatar::AAvatar()
{
	//========================================== Set Tick Every Frame
	PrimaryActorTick.bCanEverTick = true;
	//========================================== Launch Strenght
	LaunchImpulse = 175000.f;
	//========================================== Weapon
	CurrentWeapon = "None";
	//========================================== MaxHealth
	MaxHitPoints = 100.f;
	//========================================== Health
	HitPoints = 100.f;
	//========================================== Speed
	RotationSpeed = 4.f;
	//========================================== Speed
	CameraSpeed = 200.f;

	//========================================== Create Sub-Component
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBody"));
	//========================================== Change To Root-Component
	MainBody->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	LeftTracks = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftTracks"));
	//========================================== Change To Root-Component
	LeftTracks->AttachToComponent(MainBody, FAttachmentTransformRules::KeepRelativeTransform);
	//========================================== Create Sub-Component
	RightTracks = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightTracks"));
	//========================================== Change To Root-Component
	RightTracks->AttachToComponent(MainBody, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	UpperBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UpperBody"));
	//========================================== Change To Root-Component
	UpperBody->AttachToComponent(MainBody, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	LeftFan = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftFan"));
	//========================================== Change To Root-Component
	LeftFan->AttachToComponent(UpperBody, FAttachmentTransformRules::KeepRelativeTransform);
	//========================================== Create Sub-Component
	RightFan = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightFan"));
	//========================================== Change To Root-Component
	RightFan->AttachToComponent(UpperBody, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	L_GutlingGun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("L_GutlingGun"));
	//========================================== Change To Root-Component
	L_GutlingGun->AttachToComponent(UpperBody, FAttachmentTransformRules::KeepRelativeTransform);
	//========================================== Create Sub-Component
	L_Barrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("L_Barrel"));
	//========================================== Change To Root-Component
	L_Barrel->AttachToComponent(L_GutlingGun, FAttachmentTransformRules::KeepRelativeTransform);
	//========================================== Create Sub-Component
	R_GutlingGun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("R_GutlingGun"));
	//========================================== Change To Root-Component
	R_GutlingGun->AttachToComponent(UpperBody, FAttachmentTransformRules::KeepRelativeTransform);
	//========================================== Create Sub-Component
	R_Barrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("R_Barrel"));
	//========================================== Change To Root-Component
	R_Barrel->AttachToComponent(R_GutlingGun, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	R_ShotParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("R_ShotParticles"));
	//========================================== Attach To Root (Default)
	R_ShotParticles->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	L_ShotParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("L_ShotParticles"));
	//========================================== Attach To Root (Default)
	L_ShotParticles->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Objectives Component
	ObjectiveComponent = CreateDefaultSubobject<UObjectivesComponent>("Objective Component");
}

//========================================== Initialize 
void AAvatar::BeginPlay()
{
	//========================================== Call Parent Setup
	Super::BeginPlay();
}

//========================================== Update
void AAvatar::Tick(float DeltaTime)
{
	//========================================== Call Parent Setup
	Super::Tick(DeltaTime);

	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	//========================================== Get Target Position & Direction
	FVector position = PController->PlayerCameraManager->GetCameraLocation();
	FRotator rotation = PController->PlayerCameraManager->GetCameraRotation();
	FVector direction = rotation.Vector();
	rotation.Pitch = 0.0f;

	RootComponent->SetWorldRotation(FMath::Lerp(RootComponent->GetComponentRotation().Quaternion(), rotation.Quaternion(), RotationSpeed * DeltaTime));

	if (!BackpackCheck(CurrentWeapon))
	{
		L_GutlingGun->SetHiddenInGame(true, true);
		R_GutlingGun->SetHiddenInGame(true, true);
	}
	else
	{
		FVector rightdirection = FVector::CrossProduct(direction, direction.UpVector);

		//========================================== Get Gun Target
		FVector L_target = (position + direction * 1000.0f);
		FVector R_target = (position + direction * 1000.0f);
		//========================================== Get Ammo Target
		FVector L_Ammo_target = L_target + (rightdirection * 50);
		FVector R_Ammo_target = R_target - (rightdirection * 50);

		//========================================== Get Gun Offset
		FVector L_Attachment = L_GutlingGun->GetComponentLocation();
		FVector R_Attachment = R_GutlingGun->GetComponentLocation();
		//========================================== Get Nozzle Offset
		FVector L_nozzleFire = L_Attachment + L_GutlingGun->GetComponentRotation().Vector() * 150;
		FVector R_nozzleFire = R_Attachment + R_GutlingGun->GetComponentRotation().Vector() * 150;

		//========================================== Set Gun/Ammo Direction
		FVector L_raycast = (L_target - L_Attachment);
		FVector R_raycast = (R_target - R_Attachment);
		FVector L_Ammo_raycast = (L_Ammo_target - L_Attachment);
		FVector R_Ammo_raycast = (R_Ammo_target - R_Attachment);
		L_raycast.Normalize();
		R_raycast.Normalize();
		L_Ammo_raycast.Normalize();
		R_Ammo_raycast.Normalize();

		if (CurrentWeapon == "GUTLING GUN")
		{
			if (Backpack[CurrentWeapon] > 0)
			{
				ABullet* L_Bullet;
				//========================================== Visualize Weapon
				L_GutlingGun->SetHiddenInGame(false, true);
				//========================================== Adjust Weapon Rotation
				L_GutlingGun->SetWorldRotation(L_raycast.Rotation());

				if (isInShooting)
				{
					//========================================== Spawn Bullets
					L_Bullet = GetWorld()->SpawnActor<ABullet>(Bullet, L_nozzleFire, L_Ammo_raycast.Rotation());
					//========================================== Shoot Bullet By Impulse
					L_Bullet->ProxSphere->AddImpulse(L_Ammo_raycast * LaunchImpulse);
				}
			}
			if (Backpack[CurrentWeapon] == 2)
			{
				ABullet* R_Bullet;
				//========================================== Visualize Weapon
				R_GutlingGun->SetHiddenInGame(false, true);
				//========================================== Adjust Weapon Rotation
				R_GutlingGun->SetWorldRotation(R_raycast.Rotation());

				if (isInShooting)
				{
					//========================================== Spawn Bullets
					R_Bullet = GetWorld()->SpawnActor<ABullet>(Bullet, R_nozzleFire, R_Ammo_raycast.Rotation());
					//========================================== Shoot Bullet By Impulse
					R_Bullet->ProxSphere->AddImpulse(R_Ammo_raycast * LaunchImpulse);
				}
			}
		}
		if (CurrentWeapon == "ROCKET LAUNCHER")
		{
			/*if (Backpack[CurrentWeapon] > 0)
			{
				L_RocketLauncher->SetWorldRotation(L_raycast.Rotation());
			}
			if (Backpack[CurrentWeapon] == 2)
			{
				R_RocketLauncher->SetWorldRotation(R_raycast.Rotation());
			}*/
		}
	}
}

//========================================== Inputs CallBacks
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//========================================== Call Parent Setup
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//========================================== Check Inputs
	check(InputComponent);
	//========================================== Inputs
	InputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	InputComponent->BindAxis("Strafe", this, &AAvatar::MoveRight);
	InputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);
	InputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
	//========================================== Actions
	InputComponent->BindAction("Particles", IE_Pressed, this, &AAvatar::ToggleParticles);
	InputComponent->BindAction("Particles", IE_Released, this, &AAvatar::ToggleParticles);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::ToggleInventory);
	InputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &AAvatar::MouseClicked);
	InputComponent->BindAction("Pause", IE_Pressed, this, &AAvatar::PauseGame);
	InputComponent->BindAction("Objectives", IE_Pressed, this, &AAvatar::ToggleObjectives);
}

void AAvatar::MoveForward(float Amount)
{
	//========================================== Enter If Ready And Pressed
	if (Controller && Amount)
	{
		FVector forward = GetActorForwardVector();
		AddMovementInput(forward, Amount);
	}
}

void AAvatar::MoveRight(float Amount)
{
	//========================================== Enter If Ready And Pressed
	if (Controller && Amount)
	{
		FVector right = GetActorRightVector();
		AddMovementInput(right, Amount);
	}
}

void AAvatar::Yaw(float Amount)
{
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	//========================================== Get Mouse Movement 
	if (InventoryShowing) 
	{   
		gui->MouseMoved();  
	}
	//========================================== Rotate By MouseX
	else
	{
		AddControllerYawInput(CameraSpeed * Amount * GetWorld()->GetDeltaSeconds());
	}
}

void AAvatar::Pitch(float Amount)
{
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	//========================================== Get Mouse Movement 
	if (InventoryShowing)
	{
		gui->MouseMoved();
	}
	//========================================== Rotate By MouseY
	else
	{
		AddControllerPitchInput(CameraSpeed * Amount * GetWorld()->GetDeltaSeconds());
	}
}

void AAvatar::ToggleParticles()
{
	isInShooting = !isInShooting;

	if (isInShooting)
	{
		R_ShotParticles->ActivateSystem();
		L_ShotParticles->ActivateSystem();
	}
	else
	{
		R_ShotParticles->DeactivateSystem();
		L_ShotParticles->DeactivateSystem();
	}
}

void AAvatar::Pickup(APickupItem* Item)
{
	//========================================== Actives resolve war with words objective when ID Card is picked up and the objective doesn't exist
	if (Item->Name == "ID Card" && !ObjectiveComponent->ResolveWarWithWords){
		ObjectiveComponent->StartResolveWarWithWordsObjective();
	}
	//========================================== Updates resolve war with words objective to part 3 when Storage Drive is picked up and the objective is currently on part 2
	if (Item->Name == "Storage Drive" && ObjectiveComponent->ResolveWarWithWords->ActivePart == ObjectiveComponent->ResolveWarWithWords->Parts[1]){
		ObjectiveComponent->ResolveWarWithWords->SetActivePart(ObjectiveComponent->ResolveWarWithWords->Parts[2]);
	}
	if (Item->Name == "GUTLING GUN" || Item->Name == "ROCKET LAUNCHER")
	{
		CurrentWeapon = Item->Name;
	}
	//========================================== Item Already Picked
	if (Backpack.Contains(Item->Name))
	{
		//========================================== Increase Item Count
		Backpack[Item->Name] += Item->Quantity;
	}
	//========================================== Item Unpicked
	else
	{
		//========================================== Add New Item
		Backpack.Add(Item->Name, Item->Quantity);
		//========================================== Add New Icon
		Icons.Add(Item->Name, Item->Icon);
		//========================================== Add New Class
		Classes.Add(Item->Name, Item->GetClass());
	}
}

void AAvatar::Drop(UClass* Item)
{
	//========================================== Spawn New Item
	//GetWorld()->SpawnActor<AActor>(Item, GetActorLocation() + GetActorForwardVector() * 200 + FVector(0, 0, 200), GetMesh()->GetComponentRotation());
}

void AAvatar::ToggleInventory()
{
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());

	//========================================== Clear If On Display
	if (InventoryShowing)
	{
		gui->ClearWidgets();
		InventoryShowing = false;
		PController->bShowMouseCursor = false;
		return;
	}
	//========================================== Display If Not Showing
	else
	{
		//========================================== Loop Through Items
		for (TMap<FString, int>::TIterator it = Backpack.CreateIterator(); it; ++it)
		{
			UTexture2D* icon = NULL;
			//========================================== Name + Value
			FString sign = it->Key + FString::Printf(TEXT(" x %d"), it->Value);
			//========================================== Widget
			if (Icons.Find(it->Key))
			{
				icon = Icons[it->Key];
				Widget widget(Icon(sign, icon), Classes[it->Key]);
				gui->AddWidget(widget);
			}
		}
		InventoryShowing = true;
		PController->bShowMouseCursor = true;
	}
}

bool AAvatar::BackpackCheck(FString name)
{
	//========================================== Check If Item Is Present
	for (auto const &tag : Backpack)
	{
		if (tag.Key == name)
		{
			return true;
		}

	}

	return false;
}

int AAvatar::BackpackQuantity(FString name)
{
	//========================================== Retrieve Item Quantity
	for (auto const &tag : Backpack)
	{
		if (tag.Key == name)
		{
			return tag.Value;
		}

	}

	return 0;
}

void AAvatar::MouseClicked()
{
	//========================================== Get Mouse Click
	if (InventoryShowing)
	{
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AGUI* gui = Cast<AGUI>(PController->GetHUD());
		//gui->MouseClicked();
	}
}

void AAvatar::Damaged(AActor* OtherActor)
{
	//========================================== Get Actor As Monster
	AMonster* Enemy = Cast<AMonster>(OtherActor);
	//========================================== Damaged
	HitPoints -= Enemy->BaseAttackDamage;
	//========================================== Died
	if (HitPoints < 0.f)
	{
		HitPoints = 0.f;
	}
}

void AAvatar::PauseGame() {
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AGUI* GUI = Cast<AGUI>(PController->GetHUD());
	if (GUI->ActiveWidget == EWidgets::InGameHUD) {
		GUI->ActiveWidget = EWidgets::PauseMenu;
		GUI->DrawPauseMenu();
	}
	else if (GUI->ActiveWidget == EWidgets::PauseMenu) {
		GUI->ActiveWidget = EWidgets::InGameHUD;
		GUI->DrawInGame();
	}
	else if (GUI->ActiveWidget == EWidgets::ObjectiveMenu) {
		GUI->ActiveWidget = EWidgets::PauseMenu;
		GUI->DrawPauseMenu();
	}
}

void AAvatar::ToggleObjectives() {
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AGUI* GUI = Cast<AGUI>(PController->GetHUD());
	if (GUI->ActiveWidget == EWidgets::InGameHUD) {
		GUI->ActiveWidget = EWidgets::ObjectiveMenu;
		GUI->DrawObjectives();
	}
	else if (GUI->ActiveWidget == EWidgets::ObjectiveMenu) {
		GUI->ActiveWidget = EWidgets::InGameHUD;
		GUI->DrawInGame();
	}
}

UObjectivesComponent* AAvatar::GetObjectiveComponent() {
	return ObjectiveComponent;
}
