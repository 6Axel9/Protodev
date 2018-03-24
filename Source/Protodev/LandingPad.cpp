// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "LandingPad.h"
#include "Avatar.h"
#include "GUI.h"
#include "EnemySpawner.h"


//========================================== Constructor
ALandingPad::ALandingPad()
{
	Action = "This is a battery charger!";

	//========================================== Create Sub-Component
	FixDevice = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThingToBeFixed"));
	FixDevice->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	FixCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionForWinning"));
	//========================================== Change To Root-Component
	FixCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Prox Sphere On Trigger CallBack
	FixCollision->OnComponentBeginOverlap.AddDynamic(this, &ALandingPad::WinPointProx);
}

//========================================== Initialize
void ALandingPad::BeginPlay()
{
	Super::BeginPlay();

}

//========================================== Update
void ALandingPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (triggered)
	{
		if (!hasSpawned)
		{
		
			for (int i = 0; i < 3; i++)
			{
				AEnemySpawner * enemy = GetWorld()->SpawnActor<AEnemySpawner>(Spawner, GetActorLocation() + FVector(-500.0f, -1500.0f,100.0f), GetActorRotation());
			}
			hasSpawned = true;

		}
	}
}

void ALandingPad::Prox_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar == nullptr)
	{
		return;
	}
	//========================================== Return If Not Avatar
	if (avatar->Part.Num() > 0)
	{
		//========================================== Check If No Parts Available
		if (avatar->Part["ContactStarFleet"] == "->Reach the Landing Pad \n->Kill all the enemies")
		{
			triggered = true;
		}
	}
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
}


void ALandingPad:: WinPointProx_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar == nullptr)
	{
		return;
	}

	//========================================== Return If Not Avatar
	if (avatar->Part.Num() > 0)
	{
		//========================================== Check If No Parts Available
		if (avatar->Part["ContactStarFleet"] == "->Reach the Landing Pad \n->Kill all the enemies" && hasSpawned)
		{
			WonGame = true;
		}
	}
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
}


