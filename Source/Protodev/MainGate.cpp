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
	////========================================== Create Sub-Component
	//mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	////========================================== Change To Root-Component
	//mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

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

//	staticmesh1->SetHiddenInGame(false);
//	staticmesh2->SetHiddenInGame(true);
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

	//if (timesinceLastOpen > 20)
	//{
	//	triggered = true;
	//	open = false;
	//}

	//if (timesinceLastOpen > 25)
	//{
	//	triggered = false;
	//	open = true;
	//	timesinceLastOpen = 0;
	//}

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


	/*mesh->PlayAnimation(animation_open, false);*/

	triggered = true;
	open = false;

	if(GateOpenAudio){
		UGameplayStatics::PlaySoundAtLocation(this, GateOpenAudio, GetActorLocation() + FVector(0, 400, 0));
		UGameplayStatics::PlaySoundAtLocation(this, GateOpenAudio, GetActorLocation() + FVector(0, -400, 0));
	}
	
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
	
}


void AMainGate::OutProx_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (avatar == nullptr)
	{

		return;
	}
	//========================================== Avatar Exit From Sight Range
	
	Action = "Bye!";
		

	/*mesh->PlayAnimation(animation_close, false);*/

	triggered = false;
	open = true;

	if(GateOpenAudio){
		UGameplayStatics::PlaySoundAtLocation(this, GateOpenAudio, GetActorLocation() + FVector(0, 400, 0));
		UGameplayStatics::PlaySoundAtLocation(this, GateOpenAudio, GetActorLocation() + FVector(0, -400, 0));
	}

	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	gui->AddMessage(Message(Action, Button, FColor::Black, FColor::White, 5.f));
	
}

