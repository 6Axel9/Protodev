#pragma once

#include "GameFramework/Actor.h"
#include "Interactive.generated.h"

UCLASS()
class PROTODEV_API AInteractive : public AActor
{
	GENERATED_BODY()

public:
	//========================================== Constructor
	AInteractive();

protected:
	//========================================== Initialize
	virtual void BeginPlay() override;

public:	

	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
		bool WonGame;

	//========================================== Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
		bool triggered;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
		FString Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
		UTexture2D* Button;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
		UBoxComponent* CollisionBox;
	//========================================== OnBeginOverlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	//========================================== Interactions
	void Damaged(AActor* OtherActor);
};
