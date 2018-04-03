// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "MainComputer.h"
#include "Avatar.h"
#include "GUI.h"


//========================================== Constructor
AMainComputer::AMainComputer()
{
	Action = "This is the old computer but there is no power..";

	//========================================== Create Sub-Component
	ComputerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Computer mesh"));
	//========================================== Attach To Root (Default)
	ComputerMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

//========================================== Initialize
void AMainComputer::BeginPlay()
{
	Super::BeginPlay();

}

//========================================== Update
void AMainComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!triggered)
	{
	}
	else
	{
	}
}

void AMainComputer::Prox_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar == nullptr)
	{
		return;
	}

	//========================================== Return If Not Avatar
	if (avatar->Part.Num() > 0)
	{
		if (avatar->Backpack.Contains("Battery Pack") && avatar->Part["ContactStarFleet"] == "->Find the main computer \n->Use it to contact the rescue party")
		{
			avatar->Missions["ContactStarFleet"]++;
			avatar->Part["ContactStarFleet"] = "->Wait for the escape ship \n->Survive enemy waves";
			avatar->Backpack.Remove("Battery Pack");

			triggered = true;
		}
	}
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
}


