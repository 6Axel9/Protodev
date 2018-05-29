#pragma once

#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

UCLASS()
class PROTODEV_API APickupItem : public AActor
{
	GENERATED_BODY()

public:
	//========================================== Constructor
	APickupItem();


protected:
	//========================================== Initialize
	virtual void BeginPlay() override;

public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	//========================================== Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		int32 Quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		UTexture2D* Icon;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Item)
		USphereComponent* ProxSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Item)
		UBoxComponent* ProxQuad;

	//========================================== Audio Properties
	UAudioComponent* PickupAudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
		USoundCue* PickupItemAudio;

	//========================================== OnBeginOverlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


};
