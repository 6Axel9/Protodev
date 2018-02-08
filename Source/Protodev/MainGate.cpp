// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "PickupItem.h"
#include "Avatar.h"
#include "GUI.h"
#include "MainGate.h"




//========================================== Constructor
AMainGate::AMainGate()
{
	Action = "Welcome traveller!";

	//========================================== Create Sub-Component
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//========================================== Change To Root-Component
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


	//========================================== Create Sub-Component
	staticmesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClosedMesh"));
	//========================================== Change To Root-Component
	staticmesh1->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	staticmesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OpenedMesh"));
	//========================================== Change To Root-Component
	staticmesh2->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


	staticmesh1->SetHiddenInGame(false);
	staticmesh2->SetHiddenInGame(true);
}

//========================================== Initialize
void AMainGate::BeginPlay()
{
	Super::BeginPlay();
}


//========================================== Update
void AMainGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (triggered && timeSinceCollect <= 10)
	{

		//========================================== Atta Timer     
		timeSinceCollect += DeltaTime;
		staticmesh1->SetHiddenInGame(true);

		if (timeSinceCollect > 10)
		{
			staticmesh2->SetHiddenInGame(false);
		}
	}

}

void AMainGate::Prox_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar == nullptr)
	{
		return;
	}
	//========================================== Return If Not Avatar
	if (avatar != nullptr)
	{

		if (!triggered) 
		{ 
			mesh->PlayAnimation(animation, false); 
			triggered = true;
		}
	}
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
}

