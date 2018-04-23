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

void UProtodevGameInstance::BeginLoadingScreen(const FString& MapName)
{
	if (!IsRunningDedicatedServer() && MapName == "/Game/MyAssets/Blueprints/Level/PlayLevel")
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreen.bWaitForManualStop = false;
		LoadingScreen.MinimumLoadingScreenDisplayTime = -1;
		LoadingScreen.bMoviesAreSkippable = true;
		LoadingScreen.PlaybackType = EMoviePlaybackType::MT_Normal;
		LoadingScreen.bAllowInEarlyStartup = true;
		LoadingScreen.MoviePaths.Add(TEXT("IntroVideo"));
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
		GetMoviePlayer()->PlayMovie();
	}
}

void UProtodevGameInstance::EndLoadingScreen()
{

}


