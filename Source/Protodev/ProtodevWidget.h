// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "ProtodevWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API UProtodevWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:



	UFUNCTION(BlueprintCallable, Category="Set")
		void ActivateMainMenuWidget();
	UFUNCTION(BlueprintCallable, Category="Set")
		void ActivateInGameHUDWidget();
	UFUNCTION(BlueprintCallable, Category="Set")
		void ActivatePauseMenuWidget();
};
