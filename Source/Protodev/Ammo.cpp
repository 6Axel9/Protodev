// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Ammo.h"


//========================================== Constructor
AAmmo::AAmmo()
{
	Name = "Ammo Pack";

}

//========================================== Initialize
void AAmmo::BeginPlay()
{
	Super::BeginPlay();

}

//========================================== Update
void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Angle += DeltaTime*5.f;

	AddActorWorldOffset(FVector(0.f, 0.f, sin(Angle)*0.5f));
}