// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "PickupItem.h"
#include "Avatar.h"
#include "GUI.h"
#include "Radar.h"
#include "EnemySpawner.h"


//========================================== Constructor
ARadar::ARadar()
{

	//========================================== Create Sub-Component
	skeletalmesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//========================================== Change To Root-Component
	skeletalmesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	staticmesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//========================================== Change To Root-Component
	staticmesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	skeletalmesh->SetHiddenInGame(false);
	staticmesh->SetHiddenInGame(true);
}

//========================================== Initialize
void ARadar::BeginPlay()
{
	Super::BeginPlay();
}


//========================================== Update
void ARadar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (triggered && timeSinceActive <= 4)
	{

		//========================================== Atta Timer     
		timeSinceActive += DeltaTime;

		if (timeSinceActive > 4)
		{
			skeletalmesh->SetHiddenInGame(true);
			staticmesh->SetHiddenInGame(false);
		}
	}

	if (triggered)
	{
		if (!hasSpawned)
		{

			for (int i = 0; i < 5; i++)
			{
				AEnemySpawner * enemy = GetWorld()->SpawnActor<AEnemySpawner>(Spawner, RootComponent->GetComponentLocation() + FVector(-500.0f + i * 100, 0.0f, 0.0f), GetActorRotation());
				enemy->is_enemy_ranged_based = false;

			}

			hasSpawned = true;

		}
	}

	if (hasSpawned)
	{
		surviveCount += DeltaTime;
	}

	if (surviveCount > 180)
	{
		WonGame = true;
	}

}

void ARadar::Prox_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar == nullptr)
	{
		return;
	}
	//========================================== Return If Not Avatar
	if (avatar != nullptr)
	{
		if (avatar->Part.Num() > 0 && avatar->Part.Contains("ContactStarFleet"))
		{
			if (!triggered && avatar->Part["ContactStarFleet"] == "->Wait for the escape ship \n->Survive enemy waves")
			{
				Action = "The radar is now active and in search for a rescue party!";
				skeletalmesh->PlayAnimation(animation, false);
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


