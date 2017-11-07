// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

struct Message
{
	FString message;
	UTexture2D* icon;
	float time;
	FColor frontColor;
	FColor backColor;

	Message()
	{
		message = "DEFAULT MESSAGE";
		time = 5.f;
		frontColor = FColor::White;
		backColor = FColor::Black;
	}

	Message(FString iMessage,float iTime, FColor iFrontColor, FColor iBackColor) 
	{
		message = iMessage;     
		icon = 0;
		time = iTime;     
		frontColor = iFrontColor;
		backColor = iBackColor;
	}

	Message(FString iMessage, UTexture2D* iIcon, float iTime, FColor iFrontColor, FColor iBackColor)
	{
		message = iMessage;
		icon = iIcon;
		time = iTime;
		frontColor = iFrontColor;
		backColor = iBackColor;
	}
};

struct Icon
{
	FString name;
	UTexture2D* icon;

	Icon() 
	{ 
		name = "UNKNOWN ICON"; 
		icon = 0; 
	}
	Icon(FString& iName, UTexture2D* iIcon)
	{
		name = iName;
		icon = iIcon;
	}
};

struct Widget
{
	Icon icon;
	// in case you need to drop an item, this is the class the item was from
	UClass *className;
	FVector2D pos, size;
	Widget(Icon iIcon, UClass* iClassName)
	{
		icon = iIcon;
		className = iClassName;
	}
	float left() { return pos.X; }
	float right() { return pos.X + size.X; }
	float top() { return pos.Y; }
	float bottom() { return pos.Y + size.Y; }
	bool hit(FVector2D v)
	{
		// +---+ top (0)
		// |   |
		// +---+ bottom (2) (bottom > top)
		// L   R
		return v.X > left() && v.X < right() && v.Y > top() && v.Y < bottom();
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
	TArray<Widget> widgets;
	Widget* heldWidget;
	// Add this function to be able to draw to the HUD!   
	virtual void DrawHUD() override;

	void debug(int slot, FColor color, FString mess);

	void addMessage(Message msg);
	void addWidget(Widget widget);
	void DrawMessages();
	void DrawHealthbar();
	void DrawWidgets();

	void clearWidgets();

	FVector2D dimensions;
	
	void MouseClicked();
	void MouseMoved();
};
