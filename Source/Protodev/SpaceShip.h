// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactive.h"
#include "SpaceShip.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API ASpaceShip : public AInteractive
{
	GENERATED_BODY()
	
		ASpaceShip();


protected:
	//========================================== Initialize
	virtual void BeginPlay() override;

	float timeSinceActive;
	float surviveCount;


public:

	bool hasSpawned;
	//========================================== Weapon Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
		UClass* Spawner;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
		UBoxComponent* WinCollision;

	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	//========================================== OnBeginOverlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	bool isActive;
	
	//========================================== WinPointOverlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void WinPointProx(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
};
