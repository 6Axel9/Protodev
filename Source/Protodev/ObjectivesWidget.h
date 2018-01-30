// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "ObjectivesWidget.generated.h"

/**
 * 
 */


UCLASS()
class PROTODEV_API UObjectivesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void DisplayObjective();
	UFUNCTION(BlueprintCallable)
	bool GetObjective(int num);
	//UFUNCTION(BlueprintCallable)
	//void SetObjectiveColour(class FText* objectiveText);
};
