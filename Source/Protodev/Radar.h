// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactive.h"
#include "Radar.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API ARadar : public AInteractive
{
	GENERATED_BODY()
	
		ARadar();


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


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* skeletalmesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UAnimationAsset* animation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* staticmesh;

	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	//========================================== OnBeginOverlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	bool isActive;

};
