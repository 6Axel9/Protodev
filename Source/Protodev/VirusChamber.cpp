// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "PickupItem.h"
#include "Avatar.h"
#include "GUI.h"
#include "VirusChamber.h"

//========================================== Constructor
AVirusChamber::AVirusChamber()
{
	Action = "Virus vial is being prepared";

	//========================================== Create Sub-Component
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//========================================== Change To Root-Component
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	timeSinceCollect = 0;
}

//========================================== Initialize
void AVirusChamber::BeginPlay()
{
	Super::BeginPlay();
}


//========================================== Update
void AVirusChamber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (triggered && timeSinceCollect <= 15)
	{

		//========================================== Atta Timer     
		timeSinceCollect += DeltaTime;	
		
		if (timeSinceCollect > 15)
		{
			APickupItem * _pickupitem = GetWorld()->SpawnActor<APickupItem>(SpawnedObject, GetActorLocation() + (GetActorRotation().Vector() * 250) - FVector(0.0f,0.0f, 150.0f), GetActorRotation());
			PrimaryActorTick.bCanEverTick = false;
		}
	}

}

void AVirusChamber::Prox_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar == nullptr)
	{
		return;
	}
	//========================================== Return If Not Avatar
	if (avatar != nullptr)
	{
		if (!avatar->Backpack.Contains("Virus Vial") && !triggered)
		{
			Action = "There you go your virus!";
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
