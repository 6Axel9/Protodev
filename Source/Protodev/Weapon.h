// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class PROTODEV_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeleeWeapon)
		float AttackDamage;

	TArray<AActor*> ThingsHit;

	bool Swinging;

	class AMonster* WeaponHolder;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
		UBoxComponent* ProxBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
		UStaticMeshComponent* Mesh;
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void Swing();
	void Rest();
	
};
