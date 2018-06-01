// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "ScrewDriver.h"


//========================================== Constructor
AScrewDriver::AScrewDriver()
{
	Name = "Tool Box";
}

//========================================== Initialize
void AScrewDriver::BeginPlay()
{
	Super::BeginPlay();

}

//========================================== Update
void AScrewDriver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Angle += DeltaTime*5.f;

	AddActorWorldOffset(FVector(0.f, 0.f, sin(Angle)*0.25f));
}




