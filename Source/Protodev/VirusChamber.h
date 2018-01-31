// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactive.h"
#include "VirusChamber.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API AVirusChamber : public AInteractive
{
	GENERATED_BODY()
	

	AVirusChamber();


protected:
	//========================================== Initialize
	virtual void BeginPlay() override;

	float timeSinceCollect;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* mesh;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
		UAnimationAsset* animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawner)
		UClass* SpawnedObject;


	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	//========================================== OnBeginOverlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
	
};
