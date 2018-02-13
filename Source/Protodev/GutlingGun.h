// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupItem.h"
#include "GutlingGun.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API AGutlingGun : public APickupItem
{
	GENERATED_BODY()

		AGutlingGun();


protected:
	//========================================== Initialize
	virtual void BeginPlay() override;
	//========================================== Persistent Variables
	double Angle;


public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* barrel;



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* body;
	
	
	
};
