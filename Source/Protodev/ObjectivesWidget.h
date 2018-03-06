// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "ObjectivesComponent.h"
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
	//UFUNCTION(BlueprintCallable)
		//int32 GetObjectiveListSize();
	UFUNCTION(BlueprintCallable)
		class UObjectivesComponent* GetObjectiveComponent();

	UFUNCTION(BlueprintCallable)
		void DisplayObjective();
	UFUNCTION(BlueprintCallable)
		FString GetObjective(int num);
	UFUNCTION(BlueprintCallable)
		void UpdateObjectiveList();
	//UFUNCTION(BlueprintCallable)
	//TArray<FObjective*>* GetList();
	//UFUNCTION(BlueprintCallable)
	//void SetObjectiveColour(class FText* objectiveText);
};
