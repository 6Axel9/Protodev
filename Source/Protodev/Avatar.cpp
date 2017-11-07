// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Avatar.h"
#include "PickupItem.h"
#include "Bullet.h"
#include "MyHUD.h"

// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bullet_launch_sparks = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shooting Particles"));
	bullet_launch_sparks->AttachTo(RootComponent);

	inventoryShowing = false;
	MaxHp = 100.0f;
	Hp = 100.0f;
}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(InputComponent);

	InputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	InputComponent->BindAxis("Strafe", this, &AAvatar::MoveRight);
	InputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
	InputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AAvatar::Shoot);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::ToggleInventory);
	InputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &AAvatar::MouseClicked);
}

void AAvatar::MoveForward(float amount)
{
	// Don't enter the body of this function if Controller is   // not set up yet, or if the amount to move is equal to 0   
	if (Controller && amount)
	{
		FVector fwd = GetActorForwardVector();
		// we call AddMovementInput to actually move the
		// player by `amount` in the `fwd` direction
		AddMovementInput(fwd, amount);
	}
}

void AAvatar::MoveRight(float amount)
{
	if (Controller && amount)
	{
		FVector right = GetActorRightVector();
		AddMovementInput(right, amount);
	}
}

void AAvatar::Yaw(float amount)
{
	AddControllerYawInput(50 * amount * GetWorld()->GetDeltaSeconds());
}

void AAvatar::Pitch(float amount)
{
	AddControllerPitchInput(50 * amount * GetWorld()->GetDeltaSeconds());
}

void AAvatar::Shoot()
{
	if (BP_bullet)
	{
		FVector fwd = GetActorForwardVector() + FVector(0.0f,0.0f, 0.1f);
		FVector nozzle = GetMesh()->GetBoneLocation("index_03_r");
		nozzle += fwd * 50.0f;
		
		ABullet* _blt = GetWorld()->SpawnActor<ABullet>(BP_bullet, nozzle, RootComponent->GetComponentRotation());
		
		if (_blt)
		{
			_blt->ProxSphere->AddImpulse(fwd*bullet_launch_impulse);
			bullet_launch_sparks->ActivateSystem();
		}

		else
		{
			GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, "BULLET NOT FOUND");
		}
	}
}

void AAvatar::ToggleInventory()
{
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());

	// If inventory is displayed, undisplay it.
	if (inventoryShowing)
	{
		hud->clearWidgets();
		inventoryShowing = false;
		PController->bShowMouseCursor = false;
		return;
	}


	////////////////////////////////////////////////
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::White,
			"Showing inventory...");
	}
	////////////////////////////////////////////////////////

	// Otherwise, display the player's inventory
	inventoryShowing = true;
	PController->bShowMouseCursor = true;
	for (TMap<FString, int>::TIterator it = Backpack.CreateIterator(); it; ++it)
	{

		// Combine string name of the item, with qty eg Cow x 5
		FString fs = it->Key + FString::Printf(TEXT(" x %d"), it->Value);
		UTexture2D* tex = NULL;
		if (Icons.Find(it->Key))
		{
			tex = Icons[it->Key];
			Widget w(Icon(fs, tex), Classes[it->Key]);
			hud->addWidget(w);
		}
	}
}

void AAvatar::Pickup(APickupItem* item)
{
	if (Backpack.Contains(item->Name))
	{
		// the item was already in the pack.. so increase qty of it
		Backpack[item->Name] += item->Quantity;
	}
	else
	{
		// the item wasn't in the pack before, just add it in now
		Backpack.Add(item->Name, item->Quantity);

		// record the a ref to the tex the first time it is picked up
		Icons.Add(item->Name, item->Icon);

		// for instantiation later
		Classes.Add(item->Name, item->GetClass());
	}
}

void AAvatar::Drop(UClass* className)
{
	GetWorld()->SpawnActor<AActor>(
		className, GetActorLocation() + GetActorForwardVector() * 200 + FVector(0, 0, 200),
		//GetMesh()->GetTransformMatrix().Rotator());
		GetMesh()->GetComponentRotation());
}

void AAvatar::MouseClicked()
{
	if (inventoryShowing)
	{
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->MouseClicked();
	}
}