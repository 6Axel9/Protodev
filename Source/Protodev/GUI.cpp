#include "Protodev.h"
#include "Avatar.h"
#include "GUI.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

AGUI::AGUI(){
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
}

void AGUI::DrawHUD()
{
	/*if(ActiveWidget == EWidgets::MainMenu){
		if (GEngine)
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, "main menu");
		if(BP_widget){
			BP_widget->RemoveFromViewport();
		}
		BP_widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), MainMenuWidget);
		BP_widget->AddToViewport();
	}
	if(ActiveWidget == EWidgets::InGameHUD){
		if (GEngine)
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, "in game");
		if(BP_widget){
			BP_widget->RemoveFromViewport();
		}
		BP_widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), InGameHUDWidget);
		BP_widget->AddToViewport();
	}
	if(ActiveWidget == EWidgets::PauseMenu){
		if (GEngine)
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, "pause menu");
		if(PlayerController){
			PlayerController->bShowMouseCursor = true;
		}
		if(BP_widget){
			BP_widget->RemoveFromViewport();
		}
		BP_widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), PauseMenuWidget);
		BP_widget->AddToViewport();
	}
	if (ActiveWidget == EWidgets::ObjectiveMenu) {
		if (GEngine)
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, "objective menu");
		if (PlayerController) {
			PlayerController->bShowMouseCursor = true;
		}
		if (BP_widget) {
			BP_widget->RemoveFromViewport();
		}
		BP_widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), ObjectivesWidget);
		BP_widget->AddToViewport();
	}*/
	
	//========================================== Call Parent Setup
	Super::DrawHUD();
	//========================================== Set Interface Area	
	Dimensions.X = Canvas->SizeX;
	Dimensions.Y = Canvas->SizeY;
	//========================================== Draw Interface Components
	DrawHealthbar();
	DrawMessages();
	DrawWidgets();
	DrawPointer();
}

void AGUI::DrawHealthbar()
{
	//========================================== Get Player Pawn As Avatar
	AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	//========================================== Set Health Bar Size
	float Width = 200.f, Height = 50.f, Pad = 12.f, Margin = 50.f;
	//========================================== Get Per HP Size
	float Hp = avatar->HitPoints / avatar->MaxHitPoints;

	//========================================== Draw Bar Back
	DrawRect(FLinearColor(0, 0, 0, 1), Canvas->SizeX - Width - Pad - Margin, Canvas->SizeY - Height - Pad - Margin, Width + 2 * Pad, Height + 2 * Pad);
	DrawRect(FLinearColor(1 - Hp, Hp, 0, 1), Canvas->SizeX - Width - Margin, Canvas->SizeY - Height - Margin, Width * Hp, Height);
}

void AGUI::DrawMessages()
{
	//========================================== Output Messages
	for (int c = Messages.Num() - 1; c >= 0; c--)
	{
		//========================================== Background Size
		float Width, Height, Pad = 10.f;
		//========================================== Text Size
		GetTextSize(Messages[c].message, Width, Height, Font, 1.f);
		//========================================== Set Message Size
		float messageH = Height + 2.f * Pad;
		float posX = 0.f, posY = c * messageH;
		
		if (Messages[c].icon)
		{
			//========================================== Draw Icon
			DrawTexture(Messages[c].icon, posX, posY, messageH, messageH, 0.f, 0.f, 1.f, 1.f);
		}
		else
		{
			//========================================== Draw Box
			DrawRect(FLinearColor::Red, posX, posY, messageH, messageH);
		}
		//========================================== Draw Message Background
		DrawRect(FLinearColor::Transparent, posX, posY, Canvas->SizeX, messageH);
		//========================================== Draw Message Text
		DrawText(Messages[c].message, Messages[c].frontColor, messageH + posX + Pad, posY + Pad, Font);
		//========================================== Draw Message Icon
		DrawTexture(Messages[c].icon, posX, posY, messageH, messageH, 0.f, 0.f, 1.f, 1.f);
		//========================================== Spawn Timer     
		Messages[c].time -= GetWorld()->GetDeltaSeconds();
		//========================================== Remove Message     
		if (Messages[c].time < 0)
		{
			Messages.RemoveAt(c);
		}
	}
}

void AGUI::DrawWidgets()
{
	//========================================== Output Widgets
	for (int c = 0; c < Widgets.Num(); c++)
	{
		//========================================== Draw Widget Icon
		DrawTexture(Widgets[c].icon.icon, Widgets[c].pos.X, Widgets[c].pos.Y, Widgets[c].size.X, Widgets[c].size.Y, 0.f, 0.f, 1.f, 1.f);
		DrawText(Widgets[c].icon.name, FLinearColor::Red, Widgets[c].pos.X, Widgets[c].pos.Y, Font, 1.f, false);
	}
}

void AGUI::DrawPointer()
{
	//========================================== Pointer Size
	float Width = 10, Height = 10;
	//========================================== Draw Target Pointer
	DrawTexture(Pointer, Dimensions.X / 2 - Width / 2, Dimensions.Y / 2 - Height / 2, Width, Height, 0.f, 0.f, 1.f, 1.f);
}

void AGUI::AddMessage(Message iMessage)
{
	//========================================== Add To Message Container

	Messages.Add(iMessage);
	

}

void AGUI::AddWidget(Widget iWidget)
{
	//========================================== Widget Position & Size
	FVector2D start(200.f, 200.f), pad(12.f, 12.f);
	iWidget.size = FVector2D(100.f, 100.f);
	iWidget.pos = start;

	//========================================== Make Room For New Widget
	for (int c = 0; c < Widgets.Num(); c++)
	{
		//========================================== Move To Right
		iWidget.pos.X += iWidget.size.X + pad.X;
		//========================================== Move To Next Line
		if (iWidget.pos.X + iWidget.size.X > Dimensions.X)
		{
			iWidget.pos.X = start.X;
			iWidget.pos.Y += iWidget.size.Y + pad.Y;
		}
	}
	//========================================== Add To Widget Container
	Widgets.Add(iWidget);

}


bool AGUI::CheckItemByName(FString name)
{

	//========================================== Make Room For New Widget
	for (int c = 0; c < Widgets.Num(); c++)
	{
		if (Widgets[c].icon.name == name)
		{
			return true;
		}
	}
	return false;
}

void AGUI::ClearWidgets()
{
	//========================================== Empty Widget Container
	Widgets.Empty();
}

void AGUI::MouseClicked()
{
	FVector2D mouse;
	//========================================== Get Mouse Position
	APlayerController *PController = GetWorld()->GetFirstPlayerController();
	PController->GetMousePosition(mouse.X, mouse.Y);

	//========================================== Check Hit Box/Mouse Click
	for (int c = 0; c < Widgets.Num(); c++)
	{
		if (Widgets[c].Hit(mouse))
		{
			Held = &Widgets[c];
			return;
		}
	}
}

void AGUI::MouseMoved()
{
	//========================================== Get Mouse Time Since Clicked
	APlayerController *PController = GetWorld()->GetFirstPlayerController();
	float time = PController->GetInputKeyTimeDown(EKeys::LeftMouseButton);
	//========================================== Get Mouse Position
	FVector2D thisMouse, deltaMouse;
	PController->GetMousePosition(thisMouse.X, thisMouse.Y);
	//========================================== Get Mouse Movement
	static FVector2D lastMouse;
	deltaMouse = thisMouse - lastMouse;

	//========================================== Drag Widget If Held
	if (time > 0.f && Held)
	{
		Held->pos.X += deltaMouse.X;
		Held->pos.Y += deltaMouse.Y;
	}

	lastMouse = thisMouse;
}

void AGUI::SetActiveWidget(EWidgets Widget){
	ActiveWidget = Widget;
}

void AGUI::DrawObjectives() {
	if (BP_widget) {
		BP_widget->RemoveFromViewport();
	}
	BP_widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), ObjectivesWidget);
	BP_widget->AddToViewport();
	PlayerController->bShowMouseCursor = true;
}
void AGUI::DrawMainMenu() {
	if (BP_widget) {
		BP_widget->RemoveFromViewport();
	}
	BP_widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), MainMenuWidget);
	BP_widget->AddToViewport();
	PlayerController->bShowMouseCursor = true;
}

void AGUI::DrawInGame() {
	if (BP_widget) {
		BP_widget->RemoveFromViewport();
	}
	BP_widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), InGameHUDWidget);
	BP_widget->AddToViewport();
	PlayerController->bShowMouseCursor = false;
}

void AGUI::DrawPauseMenu() {
	if (BP_widget) {
		BP_widget->RemoveFromViewport();
	}
	BP_widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), PauseMenuWidget);
	BP_widget->AddToViewport();
	PlayerController->bShowMouseCursor = true;
}
