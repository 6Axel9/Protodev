// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "ProtodevGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API UProtodevGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LoadingScreenWidget;

	UPROPERTY()
		UUserWidget* LoadingWidget;

	TSharedPtr < class SWidget > loadswidget;

	UFUNCTION()
		virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
		virtual void EndLoadingScreen();
	
	
};
