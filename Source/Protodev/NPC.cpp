// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Avatar.h"
#include "NPC.h"
#include "GUI.h"


// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	impact = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Impact Particles"));
	impact->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Proximity sphere"));
	ProxSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);

	npcMessage = "HELLO IM AN AVATAR";
}

void ANPC::Prox_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<AAvatar>(OtherActor) == nullptr )
	{
		return;
	}

	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	if (PController)
	{
		AGUI * hud = Cast<AGUI>(PController->GetHUD());
		hud->AddMessage(Message(npcMessage, npcIcon, FColor::Black,FColor::White, 5.f));
	}
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ANPC::Explode()
{
	impact->ActivateSystem();
}