// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Bullet.h"
#include "Monster.h"
#include "Interactive.h"


// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Proximity sphere"));
	ProxSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::Prox);

	Damage = 1;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}


void ABullet::Prox_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp != OtherActor->GetRootComponent())
	{
		return;
	}
	AInteractive* obstacle = Cast<AInteractive>(OtherActor);
	if (obstacle != nullptr)
	{
		obstacle->Damaged(this);
	}

	AMonster* monster = Cast<AMonster>(OtherActor);
	if (monster != nullptr)
	{
		monster->Damaged(this);
	}
	Destroy();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

