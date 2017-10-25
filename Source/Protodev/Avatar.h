// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Bullet.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"


UCLASS()
class PROTODEV_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	UClass* BP_bullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float bullet_launch_impulse;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float amount);   
	void MoveRight(float amount);
	void Yaw(float amount); 
	void Pitch(float amount);

	void Shoot();

public:

	float Hp;
	float MaxHp;
};
