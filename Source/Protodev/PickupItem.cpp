#include "Protodev.h"
#include "PickupItem.h"
#include "Avatar.h"
#include "GUI.h"



//========================================== Constructor
APickupItem::APickupItem()
{
	//========================================== Set Tick Every Frame
	PrimaryActorTick.bCanEverTick = false;
	//========================================== Name
	Name = "UNKNOWN ITEM";
	//========================================== Quantity
	Quantity = 1;

	//========================================== Create Sub-Component
	ProxQuad = CreateDefaultSubobject<UBoxComponent>(TEXT("ProxQuad"));
	//========================================== Change To Root-Component
	RootComponent = ProxQuad;

	//========================================== Prox Sphere On Trigger CallBack
	ProxQuad->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::Prox);
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
	gui->AddMessage(Message(FString("Picked up ") + FString::FromInt(Quantity) + FString(" ") + Name, Icon, FColor::White, FColor::Black, 5.f));
	
	//========================================== Get Player Pawn As Avatar
	AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	//========================================== Pick Up Item
	avatar->Pickup(this);

	//========================================== Destroy Current
	Destroy();
}