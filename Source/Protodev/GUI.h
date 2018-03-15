#pragma once
#include "GameFramework/HUD.h"
#include "GUI.generated.h"

UENUM(BlueprintType)
enum class EWidgets: uint8{
	MainMenu		UMETA(DisplayName="Main Menu"),
	InGameHUD		UMETA(DisplayName="In-Game HUD"),
	PauseMenu		UMETA(DisplayName="Pause Menu")
};

//========================================== Display Hud Icon
struct Icon
{
	//========================================== Properties
	FString name;
	UTexture2D* icon;
	//========================================== Default Icon
	Icon()
	{
		name = "UNKNOWN ICON";
		icon = 0;
	}
	//========================================== Icon Overloaded
	Icon(FString& iName, UTexture2D* iIcon)
	{
		name = iName;
		icon = iIcon;
	}
};

//========================================== Display Hud Message
struct Message
{
	//========================================== Properties
	FString message;
	UTexture2D* icon;
	FColor frontColor;
	FColor backColor;
	float time;
	//========================================== Default Message
	Message()
	{
		message = "DEFAULT MESSAGE";
		frontColor = FColor::White;
		backColor = FColor::Black;
		time = 5.f;
	}
	//========================================== Message Overloaded (No Time)
	Message(FString iMessage, FColor iFrontColor)
	{
		message = iMessage;
		frontColor = iFrontColor;
	}
	//========================================== Message Overloaded (No Icon)
	Message(FString iMessage, FColor iFrontColor, FColor iBackColor, float iTime)
	{
		message = iMessage;     
		frontColor = iFrontColor;
		backColor = iBackColor;
		time = iTime;
		icon = 0;
	}
	//========================================== Message Overloaded
	Message(FString iMessage, UTexture2D* iIcon, FColor iFrontColor, FColor iBackColor, float iTime)
	{
		message = iMessage;
		frontColor = iFrontColor;
		backColor = iBackColor;
		icon = iIcon;
		time = iTime;
	}
};

//========================================== Display Hud Widget
struct Widget
{
	//========================================== Properties
	Icon icon;
	UClass *className;
	FVector2D pos, size;
	//========================================== Default Widget
	Widget(Icon iIcon, UClass* iClassName)
	{
		icon = iIcon;
		className = iClassName;
	}
	//========================================== Square Sides
	float left() { return pos.X; }
	float right() { return pos.X + size.X; }
	float top() { return pos.Y; }
	float bottom() { return pos.Y + size.Y; }
	//========================================== Hit Box
	bool Hit(FVector2D Mouse)
	{
		return Mouse.X > left() && Mouse.X < right() && Mouse.Y > top() && Mouse.Y < bottom();
	}
};

UCLASS()
class PROTODEV_API AGUI : public AHUD
{
	GENERATED_BODY()
	
public:
	//========================================== Render
	virtual void DrawHUD() override;

	//========================================== Hud Propeties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hud)
		UFont* Font;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hud)
		UTexture2D* Pointer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hud)
		UTexture2D* Hud;

	//========================================== Hud Containers
	TArray<Message> Messages;
	TArray<Message> Objectives;
	TArray<Widget> Widgets;
	FVector2D Dimensions;
	Widget* Held;

	//========================================== Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
		TSubclassOf<class UUserWidget> MainMenuWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
		TSubclassOf<class UUserWidget> InGameHUDWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
		TSubclassOf<class UUserWidget> PauseMenuWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
		TSubclassOf<class UUserWidget> ObjectivesWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
		EWidgets ActiveWidget;

	void SetActiveWidget(EWidgets Widget);
	//========================================== Add Hud Dynamically
	void AddMessage(Message iMessage);
	void AddWidget(Widget iWidget);
	void AddObjective(Message iMessage);
	//========================================== Delete Hud Dynamically
	void ClearWidgets();
	void ClearObjectives();
	//========================================== Render GUI
	void DrawHealthbar();
	void DrawMessages();
	void DrawObjectives();
	void DrawWidgets();
	void DrawPointer();
	//========================================== Mouse Inputs
	void MouseClicked();
	void MouseMoved();
};
