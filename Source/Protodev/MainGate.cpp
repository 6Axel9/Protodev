// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "PickupItem.h"
#include "Avatar.h"
#include "GUI.h"
#include "MainGate.h"




//========================================== Constructor
AMainGate::AMainGate()
{
	Action = "";
	//========================================== Create Sub-Component
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//========================================== Change To Root-Component
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Attack Sphere On Exit CallBack
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AMainGate::OutProx);

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
	if (triggered && timeSinceCollect <= 4)
	{

			if (Action == "Bye!")
			{
				////========================================== Atta Timer     
				//timeSinceCollect += DeltaTime;
				//staticmesh1->SetHiddenInGame(false);

				//if (timeSinceCollect > 4)
				//{
				//	staticmesh2->SetHiddenInGame(true);
				//	triggered = false;

				//}
			}

			else if (Action == "Welcome!")
			{
				//========================================== Atta Timer     
				timeSinceCollect += DeltaTime;
				staticmesh1->SetHiddenInGame(true);

				if (timeSinceCollect > 4)
				{
					staticmesh2->SetHiddenInGame(false);
				}
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

		Action = "Welcome!";

		if (!triggered) 
		{ 
			mesh->PlayAnimation(animation_open, false);
			timeSinceCollect = 0;
			triggered = true;
		}
		//========================================== Get Controller From Character
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		//========================================== Cast Controller As HUD
		AGUI* gui = Cast<AGUI>(PController->GetHUD());
		gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
	}
}


void AMainGate::OutProx_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar == nullptr)
	{

		return;
	}
	//========================================== Avatar Exit From Sight Range
	else
	{
		Action = "Bye!";
		/*
		if (!triggered)
		{
			timeSinceCollect = 0;
			mesh->PlayAnimation(animation_close, false);
			triggered = true;

		}*/

		//========================================== Get Controller From Character
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		//========================================== Cast Controller As HUD
		AGUI* gui = Cast<AGUI>(PController->GetHUD());
		gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
	}
}

