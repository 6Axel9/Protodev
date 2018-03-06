// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "ObjectivePart.h"

UObjectivePart::UObjectivePart(){
	Completed = false;
}

void UObjectivePart::AddPath(FString Description) {
	PathDescription.Add(Description);
};

void UObjectivePart::CompletePart() {
	Completed = true;
}


