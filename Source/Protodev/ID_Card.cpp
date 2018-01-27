// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "ID_Card.h"



//========================================== Constructor
AID_Card::AID_Card()
{
	Name = "ID Card";

}

//========================================== Initialize
void AID_Card::BeginPlay()
{
	Super::BeginPlay();

}

//========================================== Update
void AID_Card::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Angle += DeltaTime*5.f;

	AddActorWorldOffset(FVector(0.f, 0.f, sin(Angle)*0.25f));
}
