// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Objective.h"

UObjective::UObjective(){

}

void UObjective::SetObjectiveName(FString Name) {
	ObjectiveName = Name;
}

void UObjective::CompleteObjective() {
	Completed = true;
}

void UObjective::NewPart(FString partDescription){
	Parts.Add(FString(partDescription));
}

void UObjective::SetActivePart(FString activePart){
	ActivePart = activePart;
}