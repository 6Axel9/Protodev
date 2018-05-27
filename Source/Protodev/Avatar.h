#pragma once
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

class APickupItem;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* R_RocketLauncher;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RobotBody)
		UStaticMeshComponent* L_RocketLauncher;

	//========================================== Weapon Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
		UClass* Bullet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
		UClass* Rocket;

	//========================================== Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float CameraSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float HitPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float MaxHitPoints;
	//========================================== Movements CallBacks
	void MoveForward(float Amount);   
	void MoveRight(float Amount);
	void Pitch(float Amount);
	void Yaw(float Amount);
	void ToggleShooting();
	void ScrollLeft();
	void ScrollRight();
	void ScrollWeaponUp();
	void ScrollWeaponDown();
	void ScrollItemLeft();
	void ScrollItemRight();

	//========================================== Inventory Commands
	void Pickup(APickupItem *Item);
	void Drop(UClass *Item);
	void ToggleInventory();
	void MouseClicked();

	//========================================== Interactions
	void Damaged(AActor* OtherActor);
	float LaunchImpulse;
	bool isInShooting;
	int CurrentWeaponIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		TArray<FString> CollectedWeapons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		FString CurrentWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		FString CurrentAmmo;
	
	//========================================== Inventory Properties
	int CurrentItemIndex;
	TMap<FString, UClass*> Classes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
		TMap<FString, int> Backpack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
		TArray<FString> CollectedItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
		TMap<FString, UTexture2D*> Icons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
		bool InventoryShowing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
		FString CurrentItem;

	//========================================== Objective Properties
	int CurrentIndex;
	TMap<FString, int> Missions;
	TMap<FString, FString> Descriptions;
	TMap<FString, FString> Part;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objectives)
		TArray<FString> CurrentObjectives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objectives)
		FString CurrentDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objectives)
		FString CurrentPart;

	//========================================== HighScore Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HighScore)
		int CurrentScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HighScore)
		int BestScore;
	
	//========================================== FireRate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HighScore)
		int FireRateRocket;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HighScore)
		int FireRateBullet;

	float Counter;
};

