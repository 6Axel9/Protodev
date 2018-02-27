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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
		UClass* Bullet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
		UClass* Rocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
		UParticleSystemComponent* R_ShotParticles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
		UParticleSystemComponent* L_ShotParticles;

<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
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
	
	//========================================== Movements CallBacks
	void MoveForward(float Amount);   
	void MoveRight(float Amount);
	void Pitch(float Amount);
	void Yaw(float Amount);
	void ToggleParticles();
	void ShootWeapon();

	//========================================== Inventory Commands
	void Pickup(APickupItem *Item);
	void Drop(UClass *Item);
	void ToggleInventory();
	bool BackpackCheck(FString name);
	int BackpackQuantity(FString name);
	void MouseClicked();

	//========================================== Interactions
	float LaunchImpulse;
	void Damaged(AActor* OtherActor);
	bool isInShooting;
	FString CurrentWeapon;
	FVector Velocity;
	float MaxSpeed;
	float PawnYaw;

	//========================================== Inventory Property
	TMap<FString, int> Backpack;
	TMap<FString, UTexture2D*> Icons;
	TMap<FString, UClass*> Classes;
	bool InventoryShowing;

	void PauseGame();

	//========================================== Objective Commands
	void ToggleObjectives();

};
