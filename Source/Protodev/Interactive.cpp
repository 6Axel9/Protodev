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

	//========================================== Create Sub-Component
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	//========================================== Change To Root-Component
	RootComponent = CollisionBox;

	//========================================== Create Sub-Component
	ImpactParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Impact Particles"));
	//========================================== Attach To Root (Default)
	ImpactParticles->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractive::Prox);

	Action = "HELLO IM AN AVATAR";
}

void AInteractive::Prox_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<AAvatar>(OtherActor) == nullptr )
	{
		return;
	}

	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	if (PController)
	{
		AGUI * hud = Cast<AGUI>(PController->GetHUD());
		//hud->AddMessage(Message(Action, Button, FColor::Black,FColor::White, 5.f));
	}
}

// Called when the game starts or when spawned
void AInteractive::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractive::Damaged(AActor* OtherActor)
{
	//========================================== Get Actor As Monster
	ABullet* bullet = Cast<ABullet>(OtherActor);
	//========================================== Damaged At Location
	ImpactParticles->SetWorldLocation(bullet->GetActorLocation());
	ImpactParticles->ActivateSystem();
}