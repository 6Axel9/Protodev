// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class GOLDENEGG_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		float HitPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		int32 Experience;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		UClass* LootDropped;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		float BaseAttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		float AttackTimeout;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		float TimeSinceLastStrike;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		USphereComponent* SightSphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		USphereComponent* AttackRangeSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		UClass* BPMeleeWeapon;

	AActor* MeleeWeapon;

	inline bool isInSightRange(float d)
	{
		return d < SightSphere->GetScaledSphereRadius();
	}
	inline bool isInAttackRange(float d)
	{
		return d < AttackRangeSphere->GetScaledSphereRadius();
	}
	
};
