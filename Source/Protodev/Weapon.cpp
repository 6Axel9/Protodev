// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Weapon.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackDamage = 1;
	Swinging = false;
	WeaponHolder = NULL;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	ProxBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProxBox"));
	ProxBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	ProxBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::Prox);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::Prox_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp != OtherActor->GetRootComponent())
	{
		//return;
	}
	// avoid hitting things while sword isn't swinging,
	// avoid hitting yourself, and
	// avoid hitting the same OtherActor twice
	/*if (Swinging && OtherActor != WeaponHolder &&
		!ThingsHit.Contains(OtherActor))
	{
		OtherActor->TakeDamage(AttackDamage + WeaponHolder -
>BaseAttackDamage, FDamageEvent(), NULL, this);
		ThingsHit.Add(OtherActor);
	}*/
}

void AWeapon::Swing()
{
	/*ThingsHit.Empty(); // empty the list
Swinging = true;*/
}
void AWeapon::Rest()
{
	/*ThingsHit.Empty();
	Swinging = false;*/
}