// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactive.h"
#include "LandingPad.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API ALandingPad : public AInteractive
{
	GENERATED_BODY()

		ALandingPad();

protected:
	//========================================== Initialize
	virtual void BeginPlay() override;

	bool hasSpawned;
	//========================================== Weapon Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
		UClass* Spawner;
public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	//========================================== Component Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* FixDevice;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
		UBoxComponent* FixCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
		bool WonGame;
	//========================================== OnBeginOverlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	//========================================== WinPointOverlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void WinPointProx(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
