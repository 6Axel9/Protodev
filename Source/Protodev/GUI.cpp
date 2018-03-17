#include "Protodev.h"
#include "Avatar.h"
#include "GUI.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

void AGUI::DrawHUD()
{
	//========================================== Call Parent Setup
	Super::DrawHUD();
	//========================================== Set Interface Area	
	Dimensions.X = Canvas->SizeX;
	Dimensions.Y = Canvas->SizeY;
	//========================================== Draw Interface Components
	/*DrawMessages();
	DrawObjectives();
	DrawWidgets();*/
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

void AGUI::DrawObjectives()
{
	//========================================== Output Messages
	for (int c = Objectives.Num() - 1; c >= 0; c--)
	{
		//========================================== Background Size
		float Width, Height, Pad = 10.f;
		//========================================== Text Size
		GetTextSize(Objectives[c].message, Width, Height, Font, 1.f);
		//========================================== Set Message Size
		float messageH = Height + 2.f * Pad;
		float messageW = Width;
		float posX = 0.f, posY = c * messageH;

		//========================================== Draw Hud Background
		DrawTexture(Hud, posX, posY, messageW, messageH, 0.f, 0.f, 1.f, 1.f);
		//========================================== Draw Message Text
		DrawText(Objectives[c].message, Objectives[c].frontColor, messageH + posX + Pad, posY + Pad, Font);
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

void AGUI::AddObjective(Message iMessage)
{
	//========================================== Add To Message Container
	Objectives.Add(iMessage);
}

void AGUI::ClearWidgets()
{
	//========================================== Empty Widget Container
	Widgets.Empty();
}

void AGUI::ClearObjectives()
{
	//========================================== Empty Widget Container
	Objectives.Empty();
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
