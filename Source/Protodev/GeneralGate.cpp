// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "PickupItem.h"
#include "Avatar.h"
#include "GUI.h"
#include "GeneralGate.h"
#include "ObjectivesComponent.h"
#include "Objective.h"

//========================================== Constructor
AGeneralGate::AGeneralGate()
{
	Action = "Welcome";

	//========================================== Create Sub-Component
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//========================================== Change To Root-Component
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//
	////========================================== Attack Sphere On Exit CallBack
	//CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AGeneralGate::OutProx);

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
		SetActorEnableCollision(false);
	}

	else if (timeSinceCollect > 2)
	{
		timeSinceCollect = 0;
		SetActorEnableCollision(true);

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
			//================================ Checks if resolve war with words objective is on part 1 and if it is sets it to part 2;
			if(avatar->ObjectiveComponent->ResolveWarWithWords->ActivePart == avatar->ObjectiveComponent->ResolveWarWithWords->Parts[0]){
				avatar->ObjectiveComponent->ResolveWarWithWords->SetActivePart(avatar->ObjectiveComponent->ResolveWarWithWords->Parts[1]);
			}
			Action = "Welcome!";
			mesh->GlobalAnimRateScale = 1;
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

//
//void AGeneralGate::OutProx_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
//{
//	AAvatar* avatar = Cast<AAvatar>(OtherActor);
//	if (avatar == nullptr)
//	{
//		return;
//	}
//	//========================================== Avatar Exit From Sight Range
//	else
//	{
//		if (avatar->BackpackCheck("ID CARD"))
//		{
//			Action = "Bye!";
//			
//			mesh->GlobalAnimRateScale = -1;
//			mesh->PlayAnimation(animation, false);
//			triggered = false;
//
//		}
//	}
//}


