// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "PC_Desk.h"
#include "Avatar.h"
#include "GUI.h"

//========================================== Constructor
APC_Desk::APC_Desk()
{
	Action = "The Pc is missing its Driver, I should go look for it!";

	//========================================== Create Sub-Component
	Desk = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Desk mesh"));
	//========================================== Attach To Root (Default)
	Desk->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	StorageDrive = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StorageDrive mesh"));
	//========================================== Attach To Root (Default)
	StorageDrive->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Desk->SetHiddenInGame(false);
	StorageDrive->SetHiddenInGame(true);
}

//========================================== Initialize
void APC_Desk::BeginPlay()
{
	Super::BeginPlay();

}

//========================================== Update
void APC_Desk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!triggered)
	{
		StorageDrive->SetHiddenInGame(true);
	}
	else
	{
		StorageDrive->SetHiddenInGame(false);
	}
}

void APC_Desk::Prox_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar == nullptr)
	{
		return;
	}
	//========================================== Return If Not Avatar
	if (avatar->Backpack.Contains("Storage Drive"))
	{
		avatar->Part["ResolveWarWithWords"] = "Reach the Landing Pad";
		avatar->Backpack.Remove("Storage Drive");

		triggered = true;
	}
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
}