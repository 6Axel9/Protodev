// Fill out your copyright notice in the Description page of Project Settings.


#include "Protodev.h"
#include "ForceField.h"
#include "GUI.h"
#include "Avatar.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>



//========================================== Constructor
AForceField::AForceField()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Force Field Created"));
	Action = "HELLO IM A FORCE FIELD DOOR";

}

//========================================== Initialize
void AForceField::BeginPlay()
{

	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Force Field Began Play"));

}

//========================================== Update
void AForceField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//========================================== Get Player Pawn As Avatar
	AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (avatar != nullptr)
	{
		if (avatar->BackpackCheck("ID CARD"))
		{
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);

		}
	}
}

////========================================== Update
//void AForceField::TriggerCanEnter()
//{
//	if (PlayerCanEnter)
//	{
//		PlayerCanEnter = false;
//	}
//	else { PlayerCanEnter = true; }
//}




