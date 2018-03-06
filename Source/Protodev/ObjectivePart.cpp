// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "ObjectivePart.h"

UObjectivePart::UObjectivePart(){
	Completed = false;
}

void UObjectivePart::SetPartDescription(FString Description) {
	PartDescription = Description;
};

void UObjectivePart::CompletePart() {
	Completed = true;
}


