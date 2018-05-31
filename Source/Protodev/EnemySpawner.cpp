// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Monster.h"
#include "EnemySpawner.h"
#include "Runtime/Engine/Public/TimerManager.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	is_enemy_ranged_based = true;
	spawnTimer = 1;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	LastPosition = GetActorLocation();

	//========================================== Atta Timer   
	FTimerManager& TimerManager = GetWorldTimerManager();
	TimerManager.SetTimer(TimerHandle_DefaultTimer, this, &AEnemySpawner::SpawnEnemy, spawnTimer, true);
}

float AEnemySpawner::RandomNumber(float min, float max)
{
	return 0.0f;
}

//========================================== Update
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawner::SpawnEnemy(){
	if (c < GROUP_SIZE)
	{

		FVector temp_pos = LastPosition + FVector(FMath::RandRange(100, 200), FMath::RandRange(100, 200), 0.0f) - FVector(FMath::RandRange(100, 200), FMath::RandRange(100, 200), 0.0f);

		AMonster* enemy = GetWorld()->SpawnActor<AMonster>(SpawnedObject, temp_pos, GetActorRotation());
		if (!is_enemy_ranged_based)
		{
			enemy->needs_range = false;
		}
		LastPosition = temp_pos;
		c++;
	}
}


FVector AEnemySpawner::RandomPointOnUnitCircle(float radius)
{
	float angle = FMath::RandRange(0.0f, PI * 2);
	float x = sin(angle) * radius;
	float y = cos(angle) * radius;


	return FVector(x, y, 0.0f);
}