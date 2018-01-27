// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "StorageDrive.h"

//========================================== Constructor
AStorageDrive::AStorageDrive()
{
	Name = "Storage Drive";

}

//========================================== Initialize
void AStorageDrive::BeginPlay()
{
	Super::BeginPlay();

}

//========================================== Update
void AStorageDrive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Angle += DeltaTime*5.f;

	AddActorWorldOffset(FVector(0.f, 0.f, sin(Angle)*0.25f));
}