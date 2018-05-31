// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "PickupItem.h"
#include "Avatar.h"
#include "GUI.h"
#include "Monster.h"
#include "MainGate.h"




//========================================== Constructor
AMainGate::AMainGate()
{
	Action = "";

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


	//========================================== Create Sub-Component
	reachpoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PointToReach"));
	//========================================== Change To Root-Component
	reachpoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

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

	if (Action == "Bye!" || Action == "Welcome")
	{
		timesinceLastOpen += DeltaTime;
	}

	if (timesinceLastOpen > 10)
	{
		triggered = true;
		open = false;
	}

	if (timesinceLastOpen > 15)
	{
		triggered = false;
		open = true;
		timesinceLastOpen = 0;
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
	
	Action = "Welcome!";

	triggered = true;
	open = false;
	
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));

	if (GateOpenAudio) {
		UGameplayStatics::PlaySoundAtLocation(this, GateOpenAudio, GetActorLocation() + FVector(0, 400, 0));
		UGameplayStatics::PlaySoundAtLocation(this, GateOpenAudio, GetActorLocation() + FVector(0, -400, 0));
	}
	
}


void AMainGate::OutProx_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar != nullptr)
	{
		//========================================== Avatar Exit From Sight Range
	
		Action = "Bye!";

		triggered = false;
		open = true;

		//========================================== Get Controller From Character
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		//========================================== Cast Controller As HUD
		AGUI* gui = Cast<AGUI>(PController->GetHUD());
		gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
	
		if (GateOpenAudio) {
			UGameplayStatics::PlaySoundAtLocation(this, GateOpenAudio, GetActorLocation() + FVector(0, 400, 0));
			UGameplayStatics::PlaySoundAtLocation(this, GateOpenAudio, GetActorLocation() + FVector(0, -400, 0));
		}
		
	}

	AMonster* monster = Cast<AMonster>(OtherActor);

	if (monster != nullptr)
	{
		monster->will_follow = true;
		monster->needs_range = false;

	}

}

