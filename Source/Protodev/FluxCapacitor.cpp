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
	_Broken_mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Broken mesh"));
	//========================================== Attach To Root (Default)
	_Broken_mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);



	//========================================== Create Sub-Component
	_Fixed_mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Fixed mesh"));
	//========================================== Attach To Root (Default)
	_Fixed_mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	_Broken_mesh->SetHiddenInGame(true);
	_Fixed_mesh->SetHiddenInGame(true);
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
		_Broken_mesh->SetHiddenInGame(false);		
	}
	else
	{
		_Broken_mesh->SetHiddenInGame(true);
		_Fixed_mesh->SetHiddenInGame(false);
	}

}

void AFluxCapacitor::Prox_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//========================================== Return If Not Avatar
	if (Cast<AAvatar>(OtherActor) != nullptr)
	{
		Action = "You fixed the flux capacitor already!";
		triggered = true;
	}
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
}

