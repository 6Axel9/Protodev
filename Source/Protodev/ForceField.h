// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactive.h"
#include "ForceField.generated.h"

/**
 * 
 */


UCLASS()
class PROTODEV_API AForceField : public AInteractive
{
	GENERATED_BODY()

public:
	//========================================== Constructor
	AForceField();


protected:
	//========================================== Initialize
	virtual void BeginPlay() override;

public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	////========================================== Properties
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	//	bool PlayerCanEnter;


	////========================================== CanEnter
	//void TriggerCanEnter();


	
};
