// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactive.h"
#include "GeneralGate.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API AGeneralGate : public AInteractive
{
	GENERATED_BODY()

		AGeneralGate();


protected:
	//========================================== Initialize
	virtual void BeginPlay() override;

	float timeSinceCollect;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
		bool open;

	bool canEnter;

	bool isInSightRange;

public:

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
	//	USkeletalMeshComponent* mesh;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	//	UAnimationAsset* animation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* staticmesh1;

	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	//========================================== OnBeginOverlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void OutProx(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
