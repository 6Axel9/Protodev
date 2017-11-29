#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class PROTODEV_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	//========================================== Constructor
	ABullet();

protected:
	//========================================== Initialize
	virtual void BeginPlay() override;

public:	
	//========================================== Update
	virtual void Tick(float DeltaTime) override;

	//========================================== Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		float Damage;
	//========================================== Component Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Bullet)
		USphereComponent* ProxSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Bullet)
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Bullet)
		UParticleSystemComponent* ImpactParticles;
	//========================================== On Hit CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	//========================================== On Particles Death CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Particles)
		void OnFinish(UParticleSystemComponent* PSystem);
};