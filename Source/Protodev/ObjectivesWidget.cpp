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

FString UObjectivesWidget::GetObjective(int num) {
	//TArray<FObjective*>* objectives;
	AAvatar* avatar = Cast<AAvatar>(GetOwningPlayerPawn());
	//ObjectivesComponent*
	UObjectivesComponent* component = avatar->GetObjectiveComponent();
	//TArray<FObjective*>* list = component->GetList();
	//FObjective* objective;
	//objectives = Cast<UObjectivesComponent>(Cast<AAvatar>(GetOwningPlayerPawn()))->GetList();
	//if (!objectives) return false;
	//for (int i = 0; i < 3; i++) {
	//if (i == num-1) {
	//TArray<FObjective*>* list = Cast<AAvatar>(GetOwningPlayerPawn())->GetObjectiveComponent()->GetList();
	//component->GetList(i)->ObjectiveName;
	//Cast<AAvatar>(GetOwningPlayerPawn())->GetObjectiveComponent()->GetList();
	//Cast<UObjectivesComponent>(Cast<AAvatar>(GetOwningPlayerPawn()))->GetList()
	//list[0].part
	//Cast<FObjective>(list[i])
	//return component->GetList(i)->ObjectiveName;
	//}
	//}
	return "nk";
	//return " ";
}

/*TArray<FObjective*>* UObjectivesWidget::GetList() {
return Cast<UObjectivesComponent>(Cast<AAvatar>(GetOwningPlayerPawn()))->GetList();
}*/

/*void UObjectivesWidget::SetObjectiveColour(FText* objectiveText) {

objectiveText->SetColorAndOpacity(FSlateColor(FColor::Blue));
}*/

void UObjectivesWidget::UpdateObjectiveList(){

}

UObjectivesComponent* UObjectivesWidget::GetObjectiveComponent(){
	return Cast<AAvatar>(GetOwningPlayerPawn())->GetObjectiveComponent();
}

/*int32 UObjectivesWidget::GetObjectiveListSize(){
	AAvatar* avatar = Cast<AAvatar>(GetOwningPlayerPawn());
	UObjectivesComponent* component = avatar->GetObjectiveComponent();
	TArray<FObjective*>* list = component->GetList();
	return list->Num;
}*/