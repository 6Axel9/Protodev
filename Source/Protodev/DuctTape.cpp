// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "DuctTape.h"



//========================================== Constructor
ADuctTape::ADuctTape()
{
	Name = "DuctTape";
}

//========================================== Initialize
void ADuctTape::BeginPlay()
{
	Super::BeginPlay();

}

//========================================== Update
void ADuctTape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Angle += DeltaTime*5.f;

	AddActorWorldOffset(FVector(0.f, 0.f, sin(Angle)*0.25f));
}

