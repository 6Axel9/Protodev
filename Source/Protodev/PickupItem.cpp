// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "PickupItem.h"
#include "Avatar.h"
#include "MyHUD.h"


// Sets default values
APickupItem::APickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = "UNKNOWN ITEM";
	Quantity = 0;

	// For pickup items, we want the MESH to simulate the physics and
	// drive the positioning of the object. The reason for that is
	// we want the unique shape of the mesh to determine the object's
	// behavior in the world, not the bounding sphere.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ProxSphere"));
	// The bounding sphere follows the mesh, so we attach the ProxSphere
	// to the mesh object here.
	ProxSphere->AttachTo(Mesh);
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::Prox);

}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

//void APickupItem::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
void APickupItem::Prox_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// if the overlapped actor is NOT the player, just return.
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return; // go back, nothing to do here.
	}

	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	hud->addMessage(Message(FString("Picked up ") + FString::FromInt(Quantity) + FString(" ") + Name, Icon, 5.f, FColor::White, FColor::Black));
	
	AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Notice use of keyword this! That is how _this_ Pickup can refer to itself.
	avatar->Pickup(this);

	// delete the pickup item from the level once it is picked up
	Destroy();
}