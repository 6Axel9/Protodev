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
	//========================================== MaxHealth
	MaxHitPoints = 100.f;
	//========================================== Health
	HitPoints = 100.f;
	//========================================== Speed
	Speed = 50.f;

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

	if (isInShooting)
	{
		////========================================== Get Controller From Character
		//APlayerController* PController = GetWorld()->GetFirstPlayerController();

		////========================================== Get Target Position & Direction
		//FVector position = PController->PlayerCameraManager->GetCameraLocation();
		//FVector direction = PController->PlayerCameraManager->GetCameraRotation().Vector();
		//FVector target = position + direction * 100.0f;

		////========================================== Get Nozzle Offset & Direction
		//FVector nozzlePos = GetMesh()->GetBoneLocation("J_L_Gun");
		//FVector laserFire = nozzlePos + (R_ShotParticles->GetComponentLocation() - nozzlePos);
		////========================================== Set Bullet Offset & Direction
		//FVector raycast = (target - laserFire) + FVector(0.f, 0.f, 50.f);
		//raycast.Normalize();

		//static ALaser* oldLaser = NULL;

		//if (oldLaser)
		//{
		//	oldLaser->Destroy();
		//}
		//ALaser* laser = GetWorld()->SpawnActor<ALaser>(Laser, laserFire, GetActorRotation());


		//oldLaser = laser;
		////========================================== Spawn Bullet At Position
		//if (laser)
		//{
		//	laser->ShootGutlingGun(laserFire, raycast.Rotation().Vector());
		//}
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
	InputComponent->BindAction("ShootGutlingGun", IE_Repeat, this, &AAvatar::ShootGutlingGun);
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
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AGUI* gui = Cast<AGUI>(PController->GetHUD());
		//gui->MouseMoved();  
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
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AGUI* gui = Cast<AGUI>(PController->GetHUD());
		gui->MouseMoved();
	}
	//========================================== Rotate By MouseY
	else
	{
		AddControllerPitchInput(Speed * Amount * GetWorld()->GetDeltaSeconds());
	}
}

void AAvatar::ShootGutlingGun()
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
	FVector nozzlePos = FVector(0.0f);
	FVector nozzleDir = FVector(0.0f);

	FVector R_nozzleFire = nozzlePos + (R_ShotParticles->GetComponentLocation() - nozzlePos);
	FVector L_nozzleFire = nozzlePos + (L_ShotParticles->GetComponentLocation() + nozzlePos);

	//========================================== Set Bullet Offset & Direction
	FVector R_raycast = (R_target - R_nozzleFire);
	R_raycast.Normalize();

	FVector L_raycast = (L_target - L_nozzleFire);
	L_raycast.Normalize();

	//========================================== Spawn Bullet At Position
	ABullet* R_bullet = GetWorld()->SpawnActor<ABullet>(Bullet, R_nozzleFire, R_raycast.Rotation());
	ABullet* L_bullet = GetWorld()->SpawnActor<ABullet>(Bullet, L_nozzleFire, L_raycast.Rotation());


	if (R_bullet && L_bullet)
	{
		//========================================== ShootGutlingGun Bullet By Impulse
		R_bullet->ProxSphere->AddImpulse(R_raycast * LaunchImpulse);
		//========================================== ShootGutlingGun Bullet By Impulse
		L_bullet->ProxSphere->AddImpulse(L_raycast * LaunchImpulse);
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
	//========================================== Make Room For New Widget
	for (auto const &tag : Backpack)
	{
		if (tag.Key == name)
		{
			return true;
		}

	}

	return false;
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