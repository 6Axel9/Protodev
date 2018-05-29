// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Rocket.generated.h"

UCLASS()
class PROTODEV_API ARocket : public AActor
{
	GENERATED_BODY()

public:
	//========================================== Constructor
	ARocket();

protected:
	//========================================== Initialize
	virtual void BeginPlay() override;

public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	//========================================== Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rocket)
		float Damage;
	TArray<AActor*> OverlappedTargets;
	//========================================== Component Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Rocket)
		USphereComponent* ProxSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Rocket)
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Rocket)
		USphereComponent* DamageSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Rocket)
		UParticleSystemComponent* ImpactParticles;
	//========================================== On Hit CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	//========================================== On Overlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//========================================== On Particles Death CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Particles)
		void OnFinish(UParticleSystemComponent* PSystem);

	float CalculateDamage(float DamageRadius, float TargetDistance);

	//========================================== Audio Properties
	UAudioComponent* BulletAudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
		USoundCue* BulletExplosionAudio;

};