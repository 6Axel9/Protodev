#include "Protodev.h"
#include "Avatar.h"
#include "PickupItem.h"
#include "Laser.h"
#include "Monster.h"
#include "Bullet.h"
#include "GUI.h"
#include "ObjectivesComponent.h"

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
	MaxSpeed = 1000.f;
	Speed = 200.f;

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
	AddActorWorldOffset(Velocity * MaxSpeed * DeltaTime);

	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	//========================================== Get Target Position & Direction
	FVector position = PController->PlayerCameraManager->GetCameraLocation();
	FRotator rotation = PController->PlayerCameraManager->GetCameraRotation();
	FVector direction = rotation.Vector();
	rotation.Pitch = 0.0f;

	GetRootComponent()->SetWorldRotation(rotation);

	
	if (!BackpackCheck(CurrentWeapon))
	{
		L_GutlingGun->SetHiddenInGame(true, true);
		R_GutlingGun->SetHiddenInGame(true, true);
	}
	else
	{
		//========================================== Call Parent Setup
		Super::Tick(DeltaTime);

		FVector L_target = (position + direction * 1000.0f);
		FVector R_target = (position + direction * 1000.0f);

		//========================================== Get Gun Offset & Direction
		FVector L_Attachment = L_GutlingGun->GetComponentLocation();
		FVector R_Attachment = R_GutlingGun->GetComponentLocation();

		if (CurrentWeapon == "GUTLING GUN")
		{
			if (Backpack[CurrentWeapon] > 0)
			{
				L_GutlingGun->SetHiddenInGame(false, true);
				//========================================== Set Gun Offset & Direction
				FVector L_raycast = (L_target - L_Attachment);
				L_raycast.Normalize();

				L_GutlingGun->SetWorldRotation(L_raycast.Rotation());
			}
			if (Backpack[CurrentWeapon] == 2)
			{
				R_GutlingGun->SetHiddenInGame(false, true);
				//========================================== Set Gun Offset & Direction
				FVector R_raycast = (R_target - R_Attachment);
				R_raycast.Normalize();

				R_GutlingGun->SetWorldRotation(R_raycast.Rotation());
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
	InputComponent->BindAction("ShootWeapon", IE_Repeat, this, &AAvatar::ShootWeapon);
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
	//========================================== Get Mouse Movement 
	if (InventoryShowing) 
	{    
		AGUI* gui = Cast<AGUI>(PController->GetHUD());
		gui->MouseMoved();  
	}
	//========================================== Rotate By MouseX
	else
	{
		AddControllerYawInput(Speed * Amount * GetWorld()->GetDeltaSeconds());
	}
}

void AAvatar::Pitch(float Amount)
{
	//========================================== Get Mouse Movement 
	if (InventoryShowing)
	{
		AGUI* gui = Cast<AGUI>(PController->GetHUD());
		gui->MouseMoved();
	}
	//========================================== Rotate By MouseY
	else
	{
		AddControllerPitchInput(Speed * Amount * GetWorld()->GetDeltaSeconds());
	}
}

void AAvatar::ShootWeapon()
{
	if (!BackpackCheck(CurrentWeapon))
	{
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AGUI* gui = Cast<AGUI>(PController->GetHUD());

		FString message = "YOU FIRST NEED A WEAPON TO SHOOT!!";

		gui->AddMessage(Message(message, Button, FColor::Black, FColor::White, 5.f));
	}
	else
	{
		//========================================== Get Controller From Character
		APlayerController* PController = GetWorld()->GetFirstPlayerController();

		//========================================== Get Target Position & Direction
		FVector position = PController->PlayerCameraManager->GetCameraLocation();
		FVector direction = PController->PlayerCameraManager->GetCameraRotation().Vector();
		FVector rightdirection = FVector::CrossProduct(direction, direction.UpVector);
		FVector R_target = (position + direction * 1000.0f) - (rightdirection * 100);
		FVector L_target = (position + direction * 1000.0f) + (rightdirection * 100);


		//========================================== Get Nozzle Offset & Direction
		FVector R_nozzleFire = R_ShotParticles->GetComponentLocation();
		FVector L_nozzleFire = L_ShotParticles->GetComponentLocation();

		//========================================== Set Bullet Offset & Direction
		FVector R_raycast = (R_target - R_nozzleFire);
		R_raycast.Normalize();
		FVector L_raycast = (L_target - L_nozzleFire);
		L_raycast.Normalize();

		
		//========================================== Spawn Ammo At Position
		if (CurrentWeapon == "GUTLING GUN")
		{
			ABullet* L_bullet;
			ABullet* R_bullet;

			if (Backpack[CurrentWeapon] > 0)
			{
				L_bullet = GetWorld()->SpawnActor<ABullet>(Bullet, L_nozzleFire, L_raycast.Rotation());
				if (L_bullet)
				{
					//========================================== ShootGutlingGun Bullet By Impulse
					L_bullet->ProxSphere->AddImpulse(L_raycast * LaunchImpulse);
				}
			}
			if (Backpack[CurrentWeapon] == 2)
			{
				R_bullet = GetWorld()->SpawnActor<ABullet>(Bullet, R_nozzleFire, R_raycast.Rotation());
				if (R_bullet)
				{
					//========================================== ShootGutlingGun Bullet By Impulse
					R_bullet->ProxSphere->AddImpulse(R_raycast * LaunchImpulse);
				}
			}
		}
		if (CurrentWeapon == "ROCKET LAUNCHER")
		{
			APlayerController* PController = GetWorld()->GetFirstPlayerController();
			AGUI* gui = Cast<AGUI>(PController->GetHUD());

			FString message = "Shooting Rockets!!";

			gui->AddMessage(Message(message, Button, FColor::Black, FColor::White, 5.f));

			//ARocket* L_rocket;
			//ARocket* R_rocket;

			//if (Backpack[currentWeapon] > 0)
			//{
			//	L_rocket = GetWorld()->SpawnActor<ARocket>(Rocket, L_nozzleFire, L_raycast.Rotation());
			//	if (L_rocket)
			//	{
			//		//========================================== ShootGutlingGun Rocket By Impulse
			//		L_rocket->ProxSphere->AddImpulse(L_raycast * LaunchImpulse);
			//	}
			//}
			//if (Backpack[currentWeapon] == 2)
			//{
			//	R_rocket = GetWorld()->SpawnActor<ARocket>(Rocket, R_nozzleFire, R_raycast.Rotation());
			//	if (R_rocket)
			//	{
			//		//========================================== ShootGutlingGun Rocket By Impulse
			//		R_rocket->ProxSphere->AddImpulse(R_raycast * LaunchImpulse);
			//	}
			//}
		}
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
	}
	else if (GUI->ActiveWidget == EWidgets::PauseMenu) {
		GUI->ActiveWidget = EWidgets::InGameHUD;
	}
}

void AAvatar::ToggleObjectives() {
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AGUI* GUI = Cast<AGUI>(PController->GetHUD());
	if (GUI->ActiveWidget == EWidgets::InGameHUD) {
		GUI->ActiveWidget = EWidgets::ObjectiveMenu;
	}
	else if (GUI->ActiveWidget == EWidgets::ObjectiveMenu) {
		GUI->ActiveWidget = EWidgets::InGameHUD;
	}
}