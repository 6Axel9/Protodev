// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "UMGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API AUMGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	
};
