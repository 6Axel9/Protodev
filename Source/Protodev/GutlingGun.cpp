// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "GutlingGun.h"



//========================================== Constructor
AGutlingGun::AGutlingGun()
{
	Name = "GUTLING GUN";
	//========================================== Create Sub-Component
	barrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//========================================== Change To Root-Component
	barrel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh2"));
	//========================================== Change To Root-Component
	body->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

//========================================== Initialize
void AGutlingGun::BeginPlay()
{
	Super::BeginPlay();

}

//========================================== Update
void AGutlingGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Angle += DeltaTime*5.f;

	AddActorWorldOffset(FVector(0.f, 0.f, sin(Angle)*0.25f));
}
