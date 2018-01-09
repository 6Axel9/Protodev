 // Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Laser.h"


// Sets default values
ALaser::ALaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//==========================================
	Acceleration = 100.f;


	//========================================== Create Sub-Component
	_start_mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("PointA"));
	//========================================== Attach To Root (Default)
	RootComponent = _start_mesh;


	//========================================== Create Sub-Component
	_target_mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("PointB"));
	//========================================== Attach To Root (Default)
	_target_mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


	laser_particles = CreateDefaultSubobject<UParticleSystemComponent>(FName("Laser_Particles"));
	laser_particles->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	shooting = true;
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

	if (shooting)
	{
		Speed = (Speed + Acceleration) * DeltaTime;
		laser_particles->SetBeamSourcePoint(0, GetRootComponent()->GetComponentLocation(), 0);
		laser_particles->SetBeamTargetPoint(0, GetRootComponent()->GetComponentLocation() + GetRootComponent()->GetComponentRotation().Vector()*200.f, 0);
	}
	else
	{
		laser_particles->SetBeamSourcePoint(0, GetRootComponent()->GetComponentLocation(), 0);
		laser_particles->SetBeamTargetPoint(0, _target_mesh->GetComponentLocation(), 0);
	}
		
	
	
}

void ALaser::shoot(FVector Position, FVector Impulse)
{
	startPos = _start_mesh->GetComponentLocation();
	endPos = _target_mesh->GetComponentLocation();
}

