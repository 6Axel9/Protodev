// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "ProtodevWidget.h"
#include "GUI.h"

void UProtodevWidget::ActivateMainMenuWidget(){
	//GUI = Cast<AGUI>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	//GUI->ActiveWidget = EWidgets::MainMenu;
}

void UProtodevWidget::ActivateInGameHUDWidget(){
	//GetWorld()->get
	//GUI = Cast<AGUI>(GetWorld()->GetAuthGameMode()->get);
	/*if (GUI) {
		GUI->ActiveWidget = EWidgets::InGameHUD;
	}*/
	/*AGUI* GUI = Cast<AGUI>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	GUI->SetActiveWidget(EWidgets::InGameHUD);
	if (GUI->ActiveWidget == EWidgets::InGameHUD) {*/
	//}
}

void UProtodevWidget::ActivatePauseMenuWidget(){
	//GUI = Cast<AGUI>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	//GUI->ActiveWidget = EWidgets::PauseMenu;
}

void UProtodevWidget::LoadLevel() {
	FLatentActionInfo LatentInfo;
	UGameplayStatics::LoadStreamLevel(this, "MantasLevel", true, true, LatentInfo);
	//UGameplayStatics::UnloadStreamLevel(this, "MainMenu", LatentInfo);
}

void UProtodevWidget::QuitGame() {
	GIsRequestingExit = 1;
}