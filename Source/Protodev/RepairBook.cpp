// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "RepairBook.h"






//========================================== Constructor
ARepairBook::ARepairBook()
{

	//========================================== Name
	Name = "Repair Book";
	//========================================== Quantity
	Quantity = 1;

}

//========================================== Initialize
void ARepairBook::BeginPlay()
{
	Super::BeginPlay();

}

//========================================== Update
void ARepairBook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Super::Tick(DeltaTime);

	Angle += DeltaTime*5.f;

	AddActorWorldOffset(FVector(0.f, 0.f, sin(Angle)*0.25f));

}
