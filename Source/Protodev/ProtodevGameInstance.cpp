// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "ProtodevGameInstance.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

void UProtodevGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UProtodevGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMap.AddUObject(this, &UProtodevGameInstance::EndLoadingScreen);

	
}

void UProtodevGameInstance::BeginLoadingScreen(const FString& InMapName)
{
	if (!IsRunningDedicatedServer())
	{
		LoadingWidget = CreateWidget<UUserWidget>(this, LoadingScreenWidget);
		loadswidget = LoadingWidget->TakeWidget();
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreen.bWaitForManualStop = true;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 3;
		LoadingScreen.WidgetLoadingScreen = loadswidget;
		//LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
		//LoadingScreen.MoviePaths.Add(TEXT("Intro"));

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
		//GetMoviePlayer()->PlayMovie();
	}
}

void UProtodevGameInstance::EndLoadingScreen()
{

}


