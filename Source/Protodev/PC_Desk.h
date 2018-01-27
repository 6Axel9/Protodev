// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactive.h"
#include "PC_Desk.generated.h"

/**
 * 
 */
UCLASS()
class PROTODEV_API APC_Desk : public AInteractive
{
	GENERATED_BODY()
	
		APC_Desk();

protected:
	//========================================== Initialize
	virtual void BeginPlay() override;

public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	//========================================== Component Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* Desk;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* StorageDrive;
	
};
