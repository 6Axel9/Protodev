// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "SpaceShip.h"
#include "Avatar.h"
#include "GUI.h"
#include "Radar.h"
#include "EnemySpawner.h"


//========================================== Constructor
ASpaceShip::ASpaceShip()
{
	Action = "The spaceship is broken";


	//========================================== Create Sub-Component
	WinCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionForWinning"));
	//========================================== Change To Root-Component
	WinCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Prox Sphere On Trigger CallBack
	WinCollision->OnComponentBeginOverlap.AddDynamic(this, &ASpaceShip::WinPointProx);

	hasSpawned = false;
}

//========================================== Initialize
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
}


//========================================== Update
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (triggered)
	{
		if (hasSpawned == false)
		{

			for (int i = 0; i < 10; i++)
			{
				AEnemySpawner * enemy = GetWorld()->SpawnActor<AEnemySpawner>(Spawner, RootComponent->GetComponentLocation() + FVector(0.0f, 0.0f, 1000.0f), GetActorRotation());
				enemy->is_enemy_ranged_based = false;

			}

			hasSpawned = true;

		}
	}

	if (hasSpawned)
	{
		surviveCount += DeltaTime;
	}

	if (surviveCount > 360)
	{
		WonGame = true;
	}

}

void ASpaceShip::Prox_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar == nullptr)
	{
		return;
	}
	//========================================== Return If Not Avatar
	if (avatar != nullptr)
	{
		if (avatar->Part.Num() > 0 && avatar->Part.Contains("FixYourShip&Leave"))
		{
			if (!triggered)
			{
				triggered = true;
			}
		}
	}


	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
}


void ASpaceShip::WinPointProx_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar == nullptr)
	{
		return;
	}

	//========================================== Return If Not Avatar
	if (avatar->Backpack.Num() > 0)
	{
		if (avatar->Backpack.Contains("Screwdriver") && avatar->Backpack.Contains("Repair Book"))
		{
			//========================================== Check If No Parts Available
			if (hasSpawned)
			{
				WonGame = true;
			}
		}

	}
	else
	{
		return;
	}
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
}
