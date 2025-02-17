// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "VirusVial.h"


//========================================== Constructor
AVirusVial::AVirusVial()
{
	Name = "Virus Vial";

}

//========================================== Initialize
void AVirusVial::BeginPlay()
{
	Super::BeginPlay();

}

//========================================== Update
void AVirusVial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Angle += DeltaTime*5.f;

	AddActorWorldOffset(FVector(0.f, 0.f, sin(Angle)*0.25f));
}


