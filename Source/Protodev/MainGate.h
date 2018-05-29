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

	float timesinceLastOpen;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interaction)
		bool open;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* staticmesh1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* staticmesh2;

	//========================================== Audio Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
		USoundCue* GateOpenAudio;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
	//	USkeletalMeshComponent* mesh;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	//	UAnimationAsset* animation_open;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	//	UAnimationAsset* animation_close;


	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	//========================================== OnBeginOverlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void OutProx(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
