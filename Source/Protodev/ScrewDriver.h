// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupItem.h"
#include "ScrewDriver.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API AScrewDriver : public APickupItem
{
	GENERATED_BODY()
	
		AScrewDriver();


protected:
	//========================================== Initialize
	virtual void BeginPlay() override;
	//========================================== Persistent Variables
	double Angle;
public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;
	
};
