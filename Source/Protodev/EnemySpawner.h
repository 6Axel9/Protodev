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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	float RandomNumber(float min, float max);

	FVector LastPosition;

public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	TArray <FVector> Positions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemiesSpawner)
		bool is_enemy_ranged_based;

	int c;
};
