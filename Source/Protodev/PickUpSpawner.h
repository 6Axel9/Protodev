// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "Spawner.h"
#include "PickUpSpawner.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API APickUpSpawner : public ASpawner
{
	GENERATED_BODY()

		APickUpSpawner();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;


	
	
};
