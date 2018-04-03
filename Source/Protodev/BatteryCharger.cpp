// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "BatteryCharger.h"
#include "Avatar.h"
#include "GUI.h"

//========================================== Constructor
ABatteryCharger::ABatteryCharger()
{
	Action = "This is a battery charger!";

	//========================================== Create Sub-Component
	Charger = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Charger mesh"));
	//========================================== Attach To Root (Default)
	Charger->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	Battery = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Battery mesh"));
	//========================================== Attach To Root (Default)
	Battery->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Charger->SetHiddenInGame(false);
	Battery->SetHiddenInGame(true);
}

//========================================== Initialize
void ABatteryCharger::BeginPlay()
{
	Super::BeginPlay();

}

//========================================== Update
void ABatteryCharger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!triggered)
	{
		Battery->SetHiddenInGame(true);
	}
	else
	{
		Battery->SetHiddenInGame(false);
	}
}

void ABatteryCharger::Prox_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar == nullptr)
	{
		return;
	}
	//========================================== Return If Not Avatar
	if (avatar->Backpack.Contains("Battery Pack"))
	{
		avatar->Missions["ContactStarFleet"]++;
		avatar->Part["ContactStarFleet"] = "->Find the main computer \n->Use it to contact the rescue party";

		triggered = true;
	}
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
}



