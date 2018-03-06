// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "ObjectivePart.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API UObjectivePart : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	bool Completed;
	UPROPERTY(BlueprintReadWrite)
	FString PartDescription;

	UObjectivePart();
	void SetPartDescription(FString Description);
	void CompletePart();
};
