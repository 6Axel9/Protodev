#include "Protodev.h"
#include "Avatar.h"
#include "PickupItem.h"
#include "Monster.h"
#include "Bullet.h"
#include "GUI.h"

//========================================== Constructor
AAvatar::AAvatar()
{
	//========================================== Set Tick Every Frame
	PrimaryActorTick.bCanEverTick = true;
	//========================================== Create Sub-Component
	BulletParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShotParticles"));
	//========================================== Attach To Root (Default)
	BulletParticles->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	LaunchImpulse = 55000.f;
	MaxHitPoints = 100.f;
	HitPoints = 100.f;
	Speed = 50.f;
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
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AAvatar::Shoot);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::ToggleInventory);
	InputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &AAvatar::MouseClicked);
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

void AAvatar::Shoot()
{
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	//========================================== Get Target Position & Direction
	FVector position = PController->PlayerCameraManager->GetCameraLocation();
	FVector direction = PController->PlayerCameraManager->GetCameraRotation().Vector();
	FVector target = position + direction * 1000.0f;

	//========================================== Get Nozzle Offset & Direction
	FVector nozzlePos = GetMesh()->GetBoneLocation("J_L_Gun");
	FVector nozzleDir = GetMesh()->GetBoneQuaternion("J_L_Gun").Vector();
	FVector nozzleFire = nozzlePos + nozzleDir * 80.f;

	//========================================== Set Bullet Offset & Direction
	FVector raycast = (target - nozzleFire) + FVector(0.f,0.f,50.f);
	raycast.Normalize();

	//========================================== Spawn Bullet At Position
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(Bullet, nozzleFire, raycast.Rotation());
		
	if (bullet)
	{
		//========================================== Shoot Bullet By Impulse
		BulletParticles->SetWorldLocation(nozzleFire);
		bullet->ProxSphere->AddImpulse(raycast * LaunchImpulse);
		BulletParticles->AddImpulse(raycast * LaunchImpulse);
		BulletParticles->ActivateSystem();
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

void AAvatar::MouseClicked()
{
	//========================================== Get Mouse Click
	if (InventoryShowing)
	{
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AGUI* gui = Cast<AGUI>(PController->GetHUD());
		gui->MouseClicked();
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