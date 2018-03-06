// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Objective.h"

UObjective::UObjective(){

}

void UObjective::SetObjectiveName(FString Name) {
	ObjectiveName = Name;
}
void UObjective::AddParts(int NumberOfParts) {
	for (int i = 0; i < NumberOfParts; i++) {
		Parts.Add(NewObject<UObjectivePart>(UObjectivePart::StaticClass()));
	}
}
void UObjective::CompleteObjective() {
	Completed = true;
}


