// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactive.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API AWeapon : public AInteractive
{
	GENERATED_BODY()
	
	

		AWeapon();


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

	virtual void shoot();

};
