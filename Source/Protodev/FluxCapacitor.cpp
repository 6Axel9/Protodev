// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Avatar.h"
#include "GUI.h"

#include "FluxCapacitor.h"




//========================================== Constructor
AFluxCapacitor::AFluxCapacitor()
{
	Action = "The flux capacitor is broken, find a way to fix it!";

	//========================================== Create Sub-Component
	FixedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fixed"));
	//========================================== Change To Root-Component
	FixedMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//========================================== Create Sub-Component
	BrokenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Broken"));
	//========================================== Change To Root-Component
	BrokenMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

//========================================== Initialize
void AFluxCapacitor::BeginPlay()
{
	Super::BeginPlay();
}


//========================================== Update
void AFluxCapacitor::Tick(float DeltaTime)
{
	if (!triggered)
	{
		BrokenMesh->SetHiddenInGame(false);
		FixedMesh->SetHiddenInGame(true);
	}
	else
	{
		BrokenMesh->SetHiddenInGame(true);
		FixedMesh->SetHiddenInGame(false);
	}

}

void AFluxCapacitor::Prox_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{


	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar == nullptr)
	{
		return;
	}
	//========================================== Return If Not Avatar
	if (avatar != nullptr)
	{
		if (avatar->Backpack.Contains("Duct Tape"))
		{
			Action = "You fixed the flux capacitor already!";
			triggered = true;
		}
	}
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
}

