// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "UMGPlayerController.h"



void AUMGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}
