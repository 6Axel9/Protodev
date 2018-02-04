// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Avatar.h"
#include "GUI.h"
#include "Weapon.h"

//========================================== Constructor
AWeapon::AWeapon()
{
	//========================================== Create Sub-Component
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//========================================== Change To Root-Component
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

//========================================== Initialize
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}


//========================================== Update
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::shoot()
{
}
