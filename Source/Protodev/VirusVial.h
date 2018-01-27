// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupItem.h"
#include "VirusVial.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API AVirusVial : public APickupItem
{

	GENERATED_BODY()

	AVirusVial();


protected:
	//========================================== Initialize
	virtual void BeginPlay() override;
	//========================================== Persistent Variables
	double Angle;
public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;
	
};
