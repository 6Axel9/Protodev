// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "ObjectivesWidget.h"
#include "TextBlock.h"
#include "ObjectivesComponent.h"
#include "Avatar.h"
#include "Text.h"

void UObjectivesWidget::DisplayObjective() {
	//UTextBlock* test;
	//test->
}

bool UObjectivesWidget::GetObjective(int num) {
	//TArray<FObjective*>* objectives;
	//FObjective* objective;
	//objectives = Cast<UObjectivesComponent>(Cast<AAvatar>(GetOwningPlayerPawn()))->GetList();
	//if (!objectives) return false;
	for (int i = 0; i < 3; i++) {
		if (i == num-1 && Cast<UObjectivesComponent>(Cast<AAvatar>(GetOwningPlayerPawn()))->GetList()->IsValidIndex(i)) {
			return true;
		}
	}
	return false;
}

/*void UObjectivesWidget::SetObjectiveColour(FText* objectiveText) {

	objectiveText->SetColorAndOpacity(FSlateColor(FColor::Blue));
}*/