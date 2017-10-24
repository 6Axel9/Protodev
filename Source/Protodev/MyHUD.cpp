// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "MyHUD.h"
#include "Avatar.h"

void AMyHUD::DrawHUD()
{
	
	// call superclass DrawHUD() function first
	Super::DrawHUD();   // then proceed to draw your stuff.
					
	dimensions.X = Canvas->SizeX;
	dimensions.Y = Canvas->SizeY;

	DrawMessages();
	DrawHealthbar();
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
		// black backing
		DrawRect(FLinearColor::Black, x, y, Canvas->SizeX, messageH);
		// draw our message using the hudFont
		DrawText(messages[c].message, messages[c].color, messageH + x + pad, y + pad, hudFont);
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


void AMyHUD::addMessage(Message msg)
{
	messages.Add(msg);
}
