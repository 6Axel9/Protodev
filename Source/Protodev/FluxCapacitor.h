// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactive.h"
#include "FluxCapacitor.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API AFluxCapacitor : public AInteractive
{
	GENERATED_BODY()
	

	AFluxCapacitor();


protected:
	//========================================== Initialize
	virtual void BeginPlay() override;


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* BrokenMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* FixedMesh;

	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	//========================================== OnBeginOverlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
};
