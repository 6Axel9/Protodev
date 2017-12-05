#pragma once
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

class APickupItem;	
class AMonster;
class ABullet;
class AGUI;

UCLASS()
class PROTODEV_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	//========================================== Constructor
	AAvatar();

protected:
	//========================================== Initialize
	virtual void BeginPlay() override;

public:
	//========================================== Update
	virtual void Tick(float DeltaTime) override;
	//========================================== Inputs CallBacks
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//========================================== Weapon Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		UClass* Bullet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		UClass* Laser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		UParticleSystemComponent* ShotParticles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		float LaunchImpulse;
	//========================================== Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float HitPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float MaxHitPoints;
	//========================================== State Properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		bool isInShooting;
	//========================================== Movements CallBacks
	void MoveForward(float Amount);   
	void MoveRight(float Amount);
	void Pitch(float Amount);
	void Yaw(float Amount);
	void Shoot();
	void LaserOn();
	void LaserOff();

	//========================================== Inventory Commands
	void Pickup(APickupItem *Item);
	void Drop(UClass *Item);
	void ToggleInventory();
	void MouseClicked();

	//========================================== Interactions
	void Damaged(AActor* OtherActor);
	
	//========================================== Inventory Property
	TMap<FString, int> Backpack;
	TMap<FString, UTexture2D*> Icons;
	TMap<FString, UClass*> Classes;
	bool InventoryShowing;

	void PauseGame();

};
