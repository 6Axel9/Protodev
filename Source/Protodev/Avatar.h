#pragma once
#include "GameFramework/Character.h"
#include "Laser.h"
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

	//========================================== Component Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* MainBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* LeftTracks;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* RightTracks;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* UpperBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* LeftFan;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* RightFan;
	//========================================== GutlingGun Properties

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* R_GutlingGun;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* L_GutlingGun;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* L_Barrel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* R_Barrel;


	//========================================== RocketLauncher Properties

	/*FUTURE
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* R_RocketLauncher;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* L_RocketLauncher;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		USkinnedMeshComponent* R_Cannon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		USkinnedMeshComponent* L_Cannon;*/


	//========================================== Weapon Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		UClass* Bullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		UClass* Laser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		UParticleSystemComponent* R_ShotParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		UParticleSystemComponent* L_ShotParticles;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		float LaunchImpulse;
	
	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category = Bullet)
		UParticleSystem* laser_particles;
	//========================================== Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float HitPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float MaxHitPoints;
	//========================================== Objective Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		class UObjectivesComponent* ObjectiveComponent;
	//========================================== State Properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		bool isInShooting;
	//========================================== Movements CallBacks
	void MoveForward(float Amount);   
	void MoveRight(float Amount);
	void Pitch(float Amount);
	void Yaw(float Amount);
	void ShootGutlingGun();
	void LaserOn();
	void LaserOff();

	void Shoot_Laser();

	//========================================== Inventory Commands
	void Pickup(APickupItem *Item);
	void Drop(UClass *Item);
	void ToggleInventory();
	bool BackpackCheck(FString name);
	void MouseClicked();

	//========================================== Interactions
	void Damaged(AActor* OtherActor);
	
	ALaser* _laser;

	//========================================== Inventory Property
	TMap<FString, int> Backpack;
	TMap<FString, UTexture2D*> Icons;
	TMap<FString, UClass*> Classes;
	bool InventoryShowing;

	void PauseGame();

	//========================================== Objective Commands
	void ToggleObjectives();

};
