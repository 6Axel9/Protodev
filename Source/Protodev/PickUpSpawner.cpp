// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "PickUpItem.h"
#include "PickUpSpawner.h"



// Sets default values
APickUpSpawner::APickUpSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickUpSpawner::BeginPlay()
{
	Super::BeginPlay();
	APickupItem * _pickupitem = GetWorld()->SpawnActor<APickupItem>(SpawnedObject, GetActorLocation(), GetActorRotation());


}

// Called every frame
void APickUpSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

