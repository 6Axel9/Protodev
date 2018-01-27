// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupItem.h"
#include "RepairBook.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API ARepairBook : public APickupItem
{
	GENERATED_BODY()
	
public:
	//========================================== Constructor
	ARepairBook();


protected:
	//========================================== Initialize
	virtual void BeginPlay() override;
	double Angle;


public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;
	
	
};
