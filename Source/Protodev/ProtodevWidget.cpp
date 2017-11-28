// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "ProtodevWidget.h"

void UProtodevWidget::ActivateMainMenuWidget(){

}

void UProtodevWidget::ActivateInGameHUDWidget(){

}

void UProtodevWidget::ActivatePauseMenuWidget(){

}

void UProtodevWidget::LoadLevel() {
	FLatentActionInfo LatentInfo;
	UGameplayStatics::LoadStreamLevel(this, "MantasLevel", true, true, LatentInfo);
	//UGameplayStatics::UnloadStreamLevel(this, "MainMenu", LatentInfo);
}

void UProtodevWidget::QuitGame() {
	GIsRequestingExit = 1;
}