// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Laser.generated.h"

UCLASS()
class PROTODEV_API ALaser : public AActor
{
	GENERATED_BODY()
	
public:	
	//========================================== Constructor
	ALaser();

	USceneComponent* _root;

	//========================================== Properties
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* laser_particles;

	UPROPERTY(EditAnywhere, category = "Origin")
		UStaticMeshComponent* _start_mesh;

	UPROPERTY(EditAnywhere, category = "Target")
		UStaticMeshComponent* _target_mesh;
		



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void shoot(FVector Position, FRotator Direction);

	//========================================== Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float Acceleration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		bool isStatic;
	
	bool shooting;
};
