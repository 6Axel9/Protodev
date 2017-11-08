// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "MyHUD.h"
#include "Avatar.h"

void AMyHUD::MouseClicked()
{
	FVector2D mouse;

	APlayerController *PController = GetWorld()->GetFirstPlayerController();
	PController->GetMousePosition(mouse.X, mouse.Y);
	//debug( 0, FColor::Yellow,
	//	FString::Printf( TEXT("mouse @ %f %f"), mouse.X, mouse.Y ) );
	// go and see if hit any widgets
	for (int c = 0; c < widgets.Num(); c++)
	{
		if (widgets[c].hit(mouse))
		{
			heldWidget = &widgets[c];
			return;
		}
	}
}

void AMyHUD::MouseMoved()
{
	APlayerController *PController = GetWorld()->GetFirstPlayerController();
	float time = PController->GetInputKeyTimeDown(EKeys::LeftMouseButton);

	static FVector2D lastMouse;
	FVector2D thisMouse, dMouse;
	PController->GetMousePosition(thisMouse.X, thisMouse.Y);
	dMouse = thisMouse - lastMouse;

	if (time > 0.f && heldWidget)
	{
		// the mouse is being held down.
		// move the widget by displacement amt
		heldWidget->pos.X += dMouse.X;
		heldWidget->pos.Y += dMouse.Y; // y inverted
	}

	lastMouse = thisMouse;
}

void AMyHUD::debug(int slot, FColor color, FString mess)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(slot, 5.f, color, mess);
	}
}

void AMyHUD::DrawHUD()
{
	
	// call superclass DrawHUD() function first
	Super::DrawHUD();   // then proceed to draw your stuff.
					
	dimensions.X = Canvas->SizeX;
	dimensions.Y = Canvas->SizeY;

	DrawMessages();
	DrawHealthbar();
	DrawWidgets();
	DrawPointer();
}

void AMyHUD::DrawMessages()
{
	//STILL TO BE IMPLEMENTED
	for (int c = messages.Num() - 1; c >= 0; c--)
	{
		// draw the background box the right size
		// for the message
		float outputWidth, outputHeight, pad = 10.f;
		GetTextSize(messages[c].message, outputWidth, outputHeight, hudFont, 1.f);
		float messageH = outputHeight + 2.f*pad;
		float x = 0.f, y = c*messageH;

		if (messages[c].icon)
		{
			DrawTexture(messages[c].icon, x, y, messageH, messageH, 0, 0, 1, 1);
		}
		else
		{
			DrawRect(FLinearColor::Red, x, y, messageH, messageH);
		}

		// black backing
		DrawRect(FLinearColor::Black, x, y, Canvas->SizeX, messageH);
		// draw our message using the hudFont
		DrawText(messages[c].message, messages[c].frontColor, messageH + x + pad, y + pad, hudFont);
		// draw our icon using the texture
		DrawTexture(messages[c].icon, x, y, messageH, messageH, 0, 0, 1, 1);
		// reduce lifetime by the time that passed since last 
		// frame.     
		messages[c].time -= GetWorld()->GetDeltaSeconds();
		// if the message's time is up, remove it     
		if (messages[c].time < 0)
		{
			messages.RemoveAt(c);
		}
		// iterate from back to front thru the list, so if we remove
		// an item while iterating, there won't be any problems  
	}
}

void AMyHUD::DrawHealthbar() 
{  
	// Draw the healthbar.  
	AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	float barWidth = 200, barHeight = 50, barPad = 12, barMargin = 50;
	float percHp = avatar->Hp / avatar->MaxHp;
	DrawRect(FLinearColor(0, 0, 0, 1), Canvas->SizeX - barWidth - barPad - barMargin, Canvas->SizeY - barHeight - barPad - barMargin, barWidth + 2 * barPad, barHeight + 2 * barPad);
	DrawRect(FLinearColor(1 - percHp, percHp, 0, 1), Canvas->SizeX - barWidth - barMargin, Canvas->SizeY - barHeight - barMargin, barWidth*percHp, barHeight);
}

void AMyHUD::DrawWidgets()
{
	for (int c = 0; c < widgets.Num(); c++)
	{
		DrawTexture(widgets[c].icon.icon, widgets[c].pos.X, widgets[c].pos.Y, widgets[c].size.X, widgets[c].size.Y, 0, 0, 1, 1);
		// draws relative to center.. don't want to use this version
		//DrawText( icons[c].name, pos, hudFont, FVector2D(.6f, .6f), FColor::Yellow );
		DrawText(widgets[c].icon.name, FLinearColor::Yellow,widgets[c].pos.X, widgets[c].pos.Y,hudFont, .6f, false);
	}
}

void AMyHUD::DrawPointer()
{
	float pointWidth = 5, pointHeight = 5;
	DrawTexture(pointer, Canvas->SizeX/2 - pointWidth, Canvas->SizeY / 2 - pointHeight, pointWidth, pointHeight, 0, 0, 1, 1);
}

void AMyHUD::addMessage(Message msg)
{
	messages.Add(msg);
}

void AMyHUD::addWidget(Widget widget)
{
	// find the pos of the widget based on the grid.
	// draw the icons..
	FVector2D start(200, 200), pad(12, 12);
	widget.size = FVector2D(100, 100);
	widget.pos = start;

	// compute the position here
	for (int c = 0; c < widgets.Num(); c++)
	{
		// Move the position to the right a bit.
		widget.pos.X += widget.size.X + pad.X;

		// If there is no more room to the right then
		// jump to the next line
		if (widget.pos.X + widget.size.X > dimensions.X)
		{
			widget.pos.X = start.X;
			widget.pos.Y += widget.size.Y + pad.Y;
		}
	}

	widgets.Add(widget);
}

void AMyHUD::clearWidgets()
{
	widgets.Empty();
}