#include "Protodev.h"
#include "PickupItem.h"
#include "Avatar.h"
#include "GUI.h"

//========================================== Constructor
APickupItem::APickupItem()
{
	//========================================== Set Tick Every Frame
	PrimaryActorTick.bCanEverTick = true;
	//========================================== Name
	Name = "UNKNOWN ITEM";
	//========================================== Quantity
	Quantity = 0;

	//========================================== Create Sub-Component
	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ProxSphere"));
	//========================================== Change To Root-Component
	RootComponent = ProxSphere;
	
	//========================================== Prox Sphere On Trigger CallBack
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::Prox);
}

//========================================== Initialize
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

//========================================== Update
void APickupItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	Angle += DeltaTime*5.f;

	AddActorWorldOffset(FVector(0.f, 0.f, sin(Angle)*0.25f));
}

void APickupItem::Prox_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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
	//hud->AddMessage(Message(FString("Picked up ") + FString::FromInt(Quantity) + FString(" ") + Name, Icon, FColor::White, FColor::Black, 5.f));
	
	//========================================== Get Player Pawn As Avatar
	AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	//========================================== Pick Up Item
	avatar->Pickup(this);

	//========================================== Destroy Current
	Destroy();
}