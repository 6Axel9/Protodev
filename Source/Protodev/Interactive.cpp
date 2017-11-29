#include "Protodev.h"
#include "Avatar.h"
#include "Interactive.h"
#include "Bullet.h"
#include "GUI.h"

//========================================== Constructor
AInteractive::AInteractive()
{
	//========================================== Set Tick Every Frame
	PrimaryActorTick.bCanEverTick = true;
	//========================================== Set Action Message
	Action = "HELLO IM AN AVATAR";

	//========================================== Create Sub-Component
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	//========================================== Change To Root-Component
	RootComponent = CollisionBox;

	//========================================== Prox Sphere On Trigger CallBack
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractive::Prox);
}

//========================================== Initialize
void AInteractive::BeginPlay()
{
	Super::BeginPlay();
	
}

//========================================== Update
void AInteractive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractive::Prox_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//========================================== Return If Not Avatar
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	//========================================== Get Controller From Character
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//========================================== Cast Controller As HUD
	AGUI* gui = Cast<AGUI>(PController->GetHUD());
	//gui->AddMessage(Message(Action, Button, FColor::Black,FColor::White, 5.f));
}

void AInteractive::Damaged(AActor* OtherActor)
{
	////========================================== Get Actor As Monster
	//ABullet* bullet = Cast<ABullet>(OtherActor);
	////========================================== Damaged At Location
	//ImpactParticles->SetWorldLocation(bullet->GetActorLocation());
	//ImpactParticles->ActivateSystem();
}