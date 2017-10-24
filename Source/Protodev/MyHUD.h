// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

struct Message
{
	FString message;
	float time;
	FColor color;

	Message()
	{
		message = "DEFAULT MESSAGE";
		time = 5.f;
		color = FColor::White;
	}

	Message(FString iMessage = "DEFAULT MESSAGE", float iTime = 5.f, FColor iColor = FColor::White) {

		message = iMessage;     
		time = iTime;     
		color = iColor;
	}



};


UCLASS()
class PROTODEV_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
		
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
		UFont* hudFont;
	
		TArray<Message> messages;
		// Add this function to be able to draw to the HUD!   
		virtual void DrawHUD() override;

		void addMessage(Message msg);
		void DrawMessages();

		FVector2D dimensions;
	
};
