// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactive.h"
#include "MainGate.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API AMainGate : public AInteractive
{
	GENERATED_BODY()
	

		AMainGate();


protected:
	//========================================== Initialize
	virtual void BeginPlay() override;

	float timeSinceCollect;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* staticmesh1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* staticmesh2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
		UAnimationAsset* animation;


	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	//========================================== OnBeginOverlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
	
};
