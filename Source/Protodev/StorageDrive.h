// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupItem.h"
#include "StorageDrive.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API AStorageDrive : public APickupItem
{
	GENERATED_BODY()


		AStorageDrive();

protected:
	//========================================== Initialize
	virtual void BeginPlay() override;
	//========================================== Persistent Variables
	double Angle;
public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;
	
};
