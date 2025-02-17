// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Spawner.h"
#include "EnemySpawner.generated.h"

/**
 * 
 */
#define GROUP_SIZE 20

class AMonster;


UCLASS()
class PROTODEV_API AEnemySpawner : public ASpawner
{
	GENERATED_BODY()

		AEnemySpawner();

	
	unsigned int  Level;

	float timeSinceSpawned;
	float spawnTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float RandomNumber(float min, float max);
	
	//========================================== Tool Function for random point on circle
	FVector RandomPointOnUnitCircle(float radius);
	
	FVector LastPosition;

	void SpawnEnemy();

public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	TArray <FVector> Positions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemiesSpawner)
		bool is_enemy_ranged_based;

	FTimerHandle TimerHandle_DefaultTimer;

	int c;
};

