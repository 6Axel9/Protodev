#pragma once

#include "Bullet.h"
#include "Avatar.h"
#include "MainGate.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class PROTODEV_API AMonster : public APawn
{
	GENERATED_BODY()

public:
	//========================================== Constructor
	AMonster();

protected:
	//========================================== Initialize
	virtual void BeginPlay() override;

	float time_since_dead;
	bool needs_death;
	AAvatar *avatar;
	AMainGate *gate;

public:	
	//========================================== Update
	virtual void Tick(float DeltaTime) override;
	//========================================== Inputs CallBacks
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//========================================== Late Initialization
	virtual void PostInitializeComponents() override;
	

	UFUNCTION(BlueprintCallable)
		bool GetNeedsToDie();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* deadAntMesh;
	//========================================== Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		float MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		float HitPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		UClass* LootDropped;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		float BaseAttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		float AttackTimeout;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		float TimeSinceLastStrike;
	//========================================== State Properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		bool isInAttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		bool isInSightRange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		bool isMoving;

	//========================================== Colliders Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Monster)
		UBoxComponent* CollisionBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		USphereComponent* SightRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		USphereComponent* AttackRange;
	//========================================== OnBeginOverlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void ProxSight(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void ProxAttack(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//========================================== OnExitOverlap CallBacks
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void OutSight(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void OutAttack(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//========================================== Interactions
	void Damaged(AActor* OtherActor, int Damage);
	//========================================== Interactions
	void DropItem(UClass* Object);

	bool needs_range;
};