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
	//========================================== Launch Strenght
	LaunchImpulse = 175000.f;
	//========================================== Weapon
	CurrentWeapon = "None";
	//========================================== MaxHealth
	MaxHitPoints = 25.f;
	//========================================== Health
	HitPoints = 25.f;
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


	if (CurrentObjectives.Num() > 0)
	{
		CurrentDescription = Descriptions[CurrentObjectives[CurrentIndex]];
		CurrentPart = Part[CurrentObjectives[CurrentIndex]];
	}

	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	//========================================== Get Target Position & Direction
	FVector position = PController->PlayerCameraManager->GetCameraLocation();
	FRotator rotation = PController->PlayerCameraManager->GetCameraRotation();
	FVector direction = rotation.Vector();
	rotation.Pitch = 0.0f;

	RootComponent->SetWorldRotation(FMath::Lerp(RootComponent->GetComponentRotation().Quaternion(), rotation.Quaternion(), RotationSpeed * DeltaTime));

	if (!Backpack.Contains(CurrentWeapon))
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

		//========================================== Loop Through Items
		if (CurrentWeapon == "GUTLING GUN")
		{
			if (Backpack[CurrentWeapon] > 0)
			{
				ABullet* L_Bullet;
				//========================================== Visualize Weapon
				L_GutlingGun->SetHiddenInGame(false, true);
				//========================================== Adjust Weapon Rotation
				L_GutlingGun->SetWorldRotation(L_raycast.Rotation());

				if (isInShooting && Backpack.Contains("Ammo Pack"))
				{
					//========================================== Spawn Bullets
					L_Bullet = GetWorld()->SpawnActor<ABullet>(Bullet, L_nozzleFire, L_Ammo_raycast.Rotation());
					//========================================== Shoot Bullet By Impulse
					L_Bullet->ProxSphere->AddImpulse(L_Ammo_raycast * LaunchImpulse);
					//========================================== Decrease Ammo Counter
					if (Backpack["Ammo Pack"] > 1)
					{
						Backpack["Ammo Pack"]--;
					}
					else
					{
						Backpack.Remove("Ammo Pack");
					}
				}
			}
			if (Backpack[CurrentWeapon] == 2)
			{
				ABullet* R_Bullet;
				//========================================== Visualize Weapon
				R_GutlingGun->SetHiddenInGame(false, true);
				//========================================== Adjust Weapon Rotation
				R_GutlingGun->SetWorldRotation(R_raycast.Rotation());

				if (isInShooting && Backpack.Contains("Ammo Pack"))
				{
					//========================================== Spawn Bullets
					R_Bullet = GetWorld()->SpawnActor<ABullet>(Bullet, R_nozzleFire, R_Ammo_raycast.Rotation());
					//========================================== Shoot Bullet By Impulse
					R_Bullet->ProxSphere->AddImpulse(R_Ammo_raycast * LaunchImpulse);
					//========================================== Decrease Ammo Counter
					if (Backpack["Ammo Pack"] > 1)
					{
						Backpack["Ammo Pack"]--;
					}
					else
					{
						Backpack.Remove("Ammo Pack");
					}
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
	InputComponent->BindAction("ObjectivesScrollR", IE_Pressed, this, &AAvatar::ScrollRight);
	InputComponent->BindAction("ObjectivesScrollL", IE_Pressed, this, &AAvatar::ScrollLeft);
	InputComponent->BindAction("Particles", IE_Pressed, this, &AAvatar::ToggleShooting);
	InputComponent->BindAction("Particles", IE_Released, this, &AAvatar::ToggleShooting);
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

void AAvatar::ToggleShooting()
{
	isInShooting = !isInShooting;
}

void AAvatar::ScrollLeft()
{
	if (CurrentIndex < 1)
	{
		CurrentIndex = CurrentObjectives.Num() - 1;
	}
	else
	{
		CurrentIndex--;
	}
}

void AAvatar::ScrollRight()
{
	if (CurrentIndex > CurrentObjectives.Num() - 2)
	{
		CurrentIndex = 0;
	}
	else
	{
		CurrentIndex++;
	}
}

void AAvatar::Pickup(APickupItem* Item)
{
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());

	//========================================== Actives ID Card Related Objectives
	if (Item->Name == "ID Card")
	{
		CurrentObjectives.Add("ContactStarFleet");
		CurrentObjectives.Add("ResolveWarWithWords");
		CurrentObjectives.Add("FixYourShip&Leave");
		Missions.Add("ContactStarFleet"   , 0);
		Missions.Add("ResolveWarWithWords", 0); 
		Missions.Add("FixYourShip&Leave"  , 0);
		Descriptions.Add("ContactStarFleet"	  , "Find a way to contact the StarFleet for a rescue party ");
		Descriptions.Add("ResolveWarWithWords", "Find a way to resolve the conflict without violence");
		Descriptions.Add("FixYourShip&Leave"  , "Find a way to fix your damaged Spaceship and leave");
		Part.Add("ContactStarFleet"	  , "-> Use the ID Card to access the Compound \n-> Locate the Battery Pack");
		Part.Add("ResolveWarWithWords", "-> Use the ID Card to access the Compound \n-> Locate the Storage Drive");
		Part.Add("FixYourShip&Leave"  , "-> Use the ID Card to access the Compound \n-> Locate the Flux Capacitor");
	}
	//========================================== Updates Battery Pack Related Mission ( Contact StarFleet )
	if (Item->Name == "Battery Pack")
	{
		if (Missions.Contains("ContactStarFleet"))
		{
			Missions["ContactStarFleet"]++;
			Part["ContactStarFleet"] = "-> Enter the Modular Base \n-> Locate the Charging Unit where to slot-in the Battery Pack";
		}
	}
	//========================================== Updates Storage Drive Related Mission ( Peacefull Resolution )
	if (Item->Name == "Storage Drive")
	{
		if (Missions.Contains("ResolveWarWithWords"))
		{
			Missions["ResolveWarWithWords"]++;
			Part["ResolveWarWithWords"] = "-> Enter the Modular Base \n-> Locate the Computer where to slot-in the Storage Drive";
		}
	}
	//========================================== Updates Storage Drive Related Mission ( Fix Your Ship )
	if (Item->Name == "Flux Capacitor")
	{
		if (Missions.Contains("FixYourShip&Leave"))
		{
			Missions["FixYourShip&Leave"]++;
			Part["FixYourShip&Leave"] = "-> Keep searching for Duct Tape \n-> Repair Book before leaving";
		}
	}
	//========================================== Set Current Weapon To Pickup
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