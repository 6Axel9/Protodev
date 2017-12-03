// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Laser.h"


// Sets default values
ALaser::ALaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//==========================================
	Acceleration = 1000.f;

	//========================================== Create Sub-Component
	_root = CreateDefaultSubobject<USceneComponent>(FName("Root"));	
	//========================================== Change To Root-Component
	RootComponent = _root;

	//========================================== Create Sub-Component
	_start_mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("PointA"));
	//========================================== Attach To Root (Default)
	_start_mesh->AttachToComponent(_root, FAttachmentTransformRules::KeepRelativeTransform);


	//========================================== Create Sub-Component
	_target_mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("PointB"));
	//========================================== Attach To Root (Default)
	_target_mesh->AttachToComponent(_root, FAttachmentTransformRules::KeepRelativeTransform);


	laser_particles = CreateDefaultSubobject<UParticleSystemComponent>(FName("Laser_Particles"));
}

// Called when the game starts or when spawned
void ALaser::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isStatic)
	{
		laser_particles->SetBeamSourcePoint(0, _start_mesh->GetComponentLocation(), 0);
		laser_particles->SetBeamTargetPoint(0, _target_mesh->GetComponentLocation(), 0);
	}
	if (shooting)
	{
		Speed = (Speed + Acceleration) * DeltaTime;
	}
}

void ALaser::shoot(FVector Position, FRotator Impulse)
{
	
	laser_particles->SetBeamSourcePoint(0, Position, 0);
	laser_particles->SetBeamTargetPoint(0, Impulse.Vector() * Speed, 0);

}

