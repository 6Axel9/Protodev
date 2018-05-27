// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "RocketAmmo.h"

//========================================== Constructor
ARocketAmmo::ARocketAmmo()
{
	Name = "Rocket Pack";

}

//========================================== Initialize
void ARocketAmmo::BeginPlay()
{
	Super::BeginPlay();

}

//========================================== Update
void ARocketAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Angle += DeltaTime*5.f;

	AddActorWorldOffset(FVector(0.f, 0.f, sin(Angle)*0.25f));
}