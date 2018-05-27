#include "Protodev.h"
#include "Avatar.h"
#include "PickupItem.h"
#include "Monster.h"
#include "Bullet.h"
#include "GUI.h"

/*
Objective Status:

ContactStarFleet = Pick ID Card -> Pick battery from compound -> charge the battery -> Put it in the main computer in the com centre (this triggers radar animation when you are out)-> Kill all the enemies while waiting for the rescue ship (3 mins then game won)

FixTheSmallEscapeShip = Pick any pickups -> Find the Duct Tape -> Fix the flux capacitor -> Reach the landing pad and kill all the enemies

FixYourShip&Leave = Find screwdriver (placeholder) and the repair book -> Reach the main ship, "fix it" and leave (cutscene to be created)

ResolveWarWithWords = Find the Storage drive -> Locate the pc and interact with it -> Facetime the leader (cutscene to be created)

*************MOST OF THE OTHER MISSIONS REQUIRE OBJECTS THAT WE DONT HAVE AND STILL HAVENT TOUGHT ON HOW TO IMPLEMENT

Also added: 

New door for restricted zone with animation (can only be opened whith id card)

Added a new item in inventory because we need the screwdriver as well

Is range based variable for enemy spawner, if false enemies spawned by that actor will always seek the player (can be set both from blueprint and c++). 

Time based objectives (e.g survive for 3 mins) will spawn enemies with the above variable false, but some initial spawners (like one every five) can be given then same property..

Some decorative particles (in the compound)

Weapons and 1500 bullets can now be found in one of the com bay

The gate opens and close every 5 mins. It stays opened for 5 sec..


ISSUES:

The two doors open and close both at the same time altough they are two different blueprints

*/


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
	RotationSpeed = 15.f;
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
	L_RocketLauncher = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("L_RocketLauncher"));
	//========================================== Change To Root-Component
	L_RocketLauncher->AttachToComponent(UpperBody, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	R_RocketLauncher = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("R_RocketLauncher"));
	//========================================== Change To Root-Component
	R_RocketLauncher->AttachToComponent(UpperBody, FAttachmentTransformRules::KeepRelativeTransform);
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
	if (CollectedItems.Num() > 0)
	{
		CurrentItem = CollectedItems[CurrentItemIndex];
	}
	if (CollectedWeapons.Num() > 0)
	{
		CurrentWeapon = CollectedWeapons[CurrentWeaponIndex];
	}

	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	//========================================== Get Target Position & Direction
	FVector position = PController->PlayerCameraManager->GetCameraLocation();
	FRotator rotation = PController->PlayerCameraManager->GetCameraRotation();
	FVector direction = rotation.Vector();
	rotation.Pitch = 0.0f;

	if (!Backpack.Contains(CurrentWeapon))
	{
		L_GutlingGun->SetHiddenInGame(true, true);
		R_GutlingGun->SetHiddenInGame(true, true);
		L_RocketLauncher->SetHiddenInGame(true, true);
		R_RocketLauncher->SetHiddenInGame(true, true);
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
			//========================================== Visualize Weapon
			L_GutlingGun->SetHiddenInGame(false, true);
			L_RocketLauncher->SetHiddenInGame(true, true);
			R_RocketLauncher->SetHiddenInGame(true, true);

			if (Backpack.Contains("Ammo Pack"))
			{
				//========================================== Switch Ammo
				CurrentAmmo = "Ammo Pack";

				if (Backpack[CurrentWeapon] > 0)
				{
					ABullet* L_Bullet;
					//========================================== Adjust Weapon Rotation
					L_GutlingGun->SetWorldRotation(L_raycast.Rotation());

					if (isInShooting)
					{
						Counter += DeltaTime;
						if (Counter > FireRateBullet)
						{
							Counter = 0;
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
						Counter += DeltaTime;
						if (Counter > FireRateBullet)
						{
							Counter = 0;
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
			}
		}
		if (CurrentWeapon == "ROCKET LAUNCHER")
		{
			//========================================== Visualize Weapon
			L_RocketLauncher->SetHiddenInGame(false, true);
			L_GutlingGun->SetHiddenInGame(true, true);
			R_GutlingGun->SetHiddenInGame(true, true);

			if (Backpack.Contains("Rocket Pack"))
			{
				//========================================== Switch Ammo
				CurrentAmmo = "Rocket Pack";

				if (Backpack[CurrentWeapon] > 0)
				{
					ABullet* L_Rocket;
					//========================================== Adjust Weapon Rotation
					L_RocketLauncher->SetWorldRotation(L_raycast.Rotation());

					if (isInShooting)
					{
						Counter += DeltaTime;
						if (Counter > FireRateRocket)
						{
							Counter = 0;
							//========================================== Spawn Bullets
							L_Rocket = GetWorld()->SpawnActor<ABullet>(Rocket, L_nozzleFire, L_Ammo_raycast.Rotation());
							//========================================== Shoot Bullet By Impulse
							L_Rocket->ProxSphere->AddImpulse(L_Ammo_raycast * LaunchImpulse);
							//========================================== Decrease Ammo Counter
							if (Backpack["Rocket Pack"] > 1)
							{
								Backpack["Rocket Pack"]--;
							}
							else
							{
								Backpack.Remove("Rocket Pack");
							}
						}
					}

				}
				if (Backpack[CurrentWeapon] == 2)
				{
					ABullet* R_Rocket;
					//========================================== Visualize Weapon
					R_RocketLauncher->SetHiddenInGame(false, true);
					//========================================== Adjust Weapon Rotation
					R_RocketLauncher->SetWorldRotation(R_raycast.Rotation());

					if (isInShooting)
					{
						Counter += DeltaTime;
						if (Counter > FireRateRocket)
						{
							Counter = 0;
							//========================================== Spawn Bullets
							R_Rocket = GetWorld()->SpawnActor<ABullet>(Rocket, R_nozzleFire, R_Ammo_raycast.Rotation());
							//========================================== Shoot Bullet By Impulse
							R_Rocket->ProxSphere->AddImpulse(R_Ammo_raycast * LaunchImpulse);
							//========================================== Decrease Ammo Counter
							if (Backpack["Rocket Pack"] > 1)
							{
								Backpack["Rocket Pack"]--;
							}
							else
							{
								Backpack.Remove("Rocket Pack");
							}
						}
					}

				}
			}
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
	InputComponent->BindAction("ItemsScrollR", IE_Pressed, this, &AAvatar::ScrollItemRight);
	InputComponent->BindAction("ItemsScrollL", IE_Pressed, this, &AAvatar::ScrollItemLeft);
	InputComponent->BindAction("WeaponsScrollU", IE_Pressed, this, &AAvatar::ScrollWeaponUp);
	InputComponent->BindAction("WeaponsScrollD", IE_Pressed, this, &AAvatar::ScrollWeaponDown);
	InputComponent->BindAction("ShootWeapon", IE_Pressed, this, &AAvatar::ToggleShooting);
	InputComponent->BindAction("ShootWeapon", IE_Released, this, &AAvatar::ToggleShooting);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::ToggleInventory);
	InputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &AAvatar::MouseClicked);
}

void AAvatar::MoveForward(float Amount)
{
	//========================================== Enter If Ready And Pressed
	if (Controller && Amount)
	{
		//========================================== Get Controller From Character
		APlayerController* PController = GetWorld()->GetFirstPlayerController();

		//========================================== Get Target Position & Direction
		FRotator rotation = PController->PlayerCameraManager->GetCameraRotation();
		rotation.Pitch = 0;
		RootComponent->SetWorldRotation(FMath::Lerp(RootComponent->GetComponentRotation().Quaternion(), rotation.Quaternion(), fabs(Amount) / RotationSpeed));

		FVector forward = GetActorForwardVector();
		AddMovementInput(forward, Amount);
	}
}

void AAvatar::MoveRight(float Amount)
{
	//========================================== Enter If Ready And Pressed
	if (Controller && Amount)
	{
		//========================================== Get Controller From Character
		APlayerController* PController = GetWorld()->GetFirstPlayerController();

		//========================================== Get Target Position & Direction
		FRotator rotation = PController->PlayerCameraManager->GetCameraRotation();
		RootComponent->SetWorldRotation(FMath::Lerp(RootComponent->GetComponentRotation().Quaternion(), rotation.Quaternion(), fabs(Amount) / RotationSpeed));

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
	if (CurrentIndex == 0)
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
	if (CurrentIndex == CurrentObjectives.Num() - 1)
	{
		CurrentIndex = 0;
	}
	else
	{
		CurrentIndex++;
	}
}

void AAvatar::ScrollWeaponUp()
{
	if (CurrentWeaponIndex == 0)
	{
		CurrentWeaponIndex = CollectedWeapons.Num() - 1;
	}
	else
	{
		CurrentWeaponIndex--;
	}
}

void AAvatar::ScrollWeaponDown()
{
	if (CurrentWeaponIndex == CollectedWeapons.Num() - 1)
	{
		CurrentWeaponIndex = 0;
	}
	else
	{
		CurrentWeaponIndex++;
	}
}

void AAvatar::ScrollItemLeft()
{
	if (CurrentItemIndex == 0)
	{
		CurrentItemIndex = CollectedItems.Num() - 1;
	}
	else
	{
		CurrentItemIndex--;
	}
}

void AAvatar::ScrollItemRight()
{
	if (CurrentItemIndex == CollectedItems.Num() - 1)
	{
		CurrentItemIndex = 0;
	}
	else
	{
		CurrentItemIndex++;
	}
}

void AAvatar::Pickup(APickupItem* Item)
{
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());

	if (Item->Name == "Duct Tape")
	{
		CurrentObjectives.Add("FixTheSmallEscapeShip");
		Missions.Add("FixTheSmallEscapeShip", 0);
		Descriptions.Add("FixTheSmallEscapeShip", "Find a way to get the two smaller ships running");
		Part.Add("FixTheSmallEscapeShip", "-> Use the Duct Tape once you on an escape ship, \n   it should fix their Flux Capacitor");
	}

	//========================================== Actives ID Card Related Objectives
	if (Item->Name == "ID Card")
	{
		CurrentObjectives.Add("ContactStarFleet");
		CurrentObjectives.Add("ResolveWarWithWords");
		Missions.Add("ContactStarFleet"   , 0);
		Missions.Add("ResolveWarWithWords", 0); 
		Descriptions.Add("ContactStarFleet"	  , "Find a way to contact the StarFleet for a rescue party ");
		Descriptions.Add("ResolveWarWithWords", "Find a way to resolve the conflict without violence");
		Part.Add("ContactStarFleet"	  , "-> Use the ID Card to access the Compound \n-> Locate the Battery Pack to power the rescue ship");
		Part.Add("ResolveWarWithWords", "-> Use the ID Card to access the Compound \n-> Locate the Storage Drive");
	}
	//========================================== Updates Battery Pack Related Mission ( Contact StarFleet ) 
	if (Item->Name == "Battery Pack") 
	{
		if (Missions.Contains("ContactStarFleet"))
		{
			Missions["ContactStarFleet"]++;
			Part["ContactStarFleet"] = "-> The battery needs charge \n-> Locate the Charging Unit ";
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

	//========================================== Fix your ship and leave
	if (Item->Name == "Screwdriver")
	{
		if (!Backpack.Contains("Repair Book"))
		{
			CurrentObjectives.Add("FixYourShip&Leave");
			Missions.Add("FixYourShip&Leave", 0);
			Descriptions.Add("FixYourShip&Leave", "Fix the crashed main ship and leave");
			Part.Add("FixYourShip&Leave", "-> Find the repair book, \n   it is somewhere in this place... ");
		}
		else
		{
			Missions["FixYourShip&Leave"]++;
			Part["FixYourShip&Leave"] = "-> Looks like you already found the repair book, \n   just reach and clear the main ship from enemies... ";
		}
	}
	//========================================== Fix your ship and leave
	if (Item->Name == "Repair Book")
	{
		if (!Backpack.Contains("Screwdriver"))
		{
			CurrentObjectives.Add("FixYourShip&Leave");
			Missions.Add("FixYourShip&Leave", 0);
			Descriptions.Add("FixYourShip&Leave", "Fix the crashed main ship and leave");
			Part.Add("FixYourShip&Leave", "-> Find the screwdriver, \n   it is somewhere in this place... ");
		}
		else
		{
			Missions["FixYourShip&Leave"]++;
			Part["FixYourShip&Leave"] = "-> Looks like you already found the screwdriver, \n   just reach and clear the main ship from enemies... ";
		}
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
		//========================================== Memorize Non Weapon Items
		if (Item->Name != "GUTLING GUN" && Item->Name != "ROCKET LAUNCHER")
		{
			CollectedItems.Add(Item->Name);
		}
		//========================================== Memorize Weapon Items
		else
		{
			CollectedWeapons.Add(Item->Name);
		}
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