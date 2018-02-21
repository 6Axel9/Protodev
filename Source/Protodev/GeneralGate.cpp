// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "PickupItem.h"
#include "Avatar.h"
#include "GUI.h"
#include "GeneralGate.h"


//========================================== Constructor
AGeneralGate::AGeneralGate()
{
	Action = "Welcome";

	//========================================== Create Sub-Component
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//========================================== Change To Root-Component
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	//========================================== Create Sub-Component
	staticmesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClosedMesh"));
	//========================================== Change To Root-Component
	staticmesh1->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	staticmesh1->SetHiddenInGame(false);
	mesh->SetHiddenInGame(true);

	triggered = false;

}

//========================================== Initialize
void AGeneralGate::BeginPlay()
{
	Super::BeginPlay();
}


//========================================== Update
void AGeneralGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (triggered && timeSinceCollect <= 2)
	{

		//========================================== Atta Timer     
		timeSinceCollect += DeltaTime;

		staticmesh1->SetHiddenInGame(true);
		mesh->SetHiddenInGame(false);

	}

}

void AGeneralGate::Prox_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar == nullptr)
	{
		return;
	}
	//========================================== Return If Not Avatar
	if (avatar != nullptr)
	{
		
		if (avatar->BackpackCheck("ID CARD"))
		{
			Action = "Welcome!";
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



