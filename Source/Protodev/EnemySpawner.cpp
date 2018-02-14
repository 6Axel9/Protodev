// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Monster.h"
#include "EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	LastPosition = GetActorLocation();
}

float AEnemySpawner::RandomNumber(float min, float max)
{
	return 0.0f;
}

//========================================== Update
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//========================================== Atta Timer     
	timeSinceSpawned += DeltaTime;
	if (c < GROUP_SIZE)
	{
		if (timeSinceSpawned > 2)
		{
			FVector temp_pos = LastPosition + FVector(FMath::RandRange(100, 200), FMath::RandRange(100, 200), 0.0f);

			AMonster* enemy = GetWorld()->SpawnActor<AMonster>(SpawnedObject, temp_pos, GetActorRotation());
			
			LastPosition = temp_pos;
			c++;
			timeSinceSpawned = 0;
		}
	}

}




