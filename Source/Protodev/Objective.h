// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObjectivePart.h"
#include "UObject/NoExportTypes.h"
#include "Objective.generated.h"

UCLASS()
class PROTODEV_API UObjective : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
		FString ObjectiveName;
	UPROPERTY(BlueprintReadWrite)
		TArray<FString> Parts;
	UPROPERTY(BlueprintReadWrite)
		FString ActivePart;
	UPROPERTY(BlueprintReadWrite)
		bool Completed;

	UObjective();
	void SetObjectiveName(FString Name);
	void NewPart(FString partDescription);
	void SetActivePart(FString activePart);
	void CompleteObjective();
};
