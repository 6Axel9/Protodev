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
		UStaticMeshComponent* WindScreen;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* InteriorBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* LeftFan;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* RightFan;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* LeftArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* LeftBarrel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* RightArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* RightBarrel;
	//========================================== Weapon Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		UClass* Bullet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		UClass* Laser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
		UParticleSystemComponent* ShotParticles;
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
	void Shoot();
	void LaserOn();
	void LaserOff();

	void Shoot_Laser();

	//========================================== Inventory Commands
	void Pickup(APickupItem *Item);
	void Drop(UClass *Item);
	void ToggleInventory();
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
