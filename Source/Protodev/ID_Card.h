// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupItem.h"
#include "ID_Card.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API AID_Card : public APickupItem
{
	GENERATED_BODY()

	AID_Card();
	

protected:
	//========================================== Initialize
	virtual void BeginPlay() override;
	//========================================== Persistent Variables
	double Angle;
public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;
	
};
