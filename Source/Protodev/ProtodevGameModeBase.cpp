// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "ProtodevGameModeBase.h"


void AProtodevGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeInGameWidget(StartingWidgetClass);
}

void AProtodevGameModeBase::ChangeInGameWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

