// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

class APickupItem; // forward declare the APickupItem class	
class ABullet;
class AMyHUD; // forward declare the AMyHud class

UCLASS()
class PROTODEV_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	UClass* BP_bullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	UParticleSystemComponent* bullet_launch_sparks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float bullet_launch_impulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	float Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	float MaxHp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Movements
	void MoveForward(float amount);   
	void MoveRight(float amount);
	void Yaw(float amount); 
	void Pitch(float amount);
	void Shoot();

	// Inventory
	void Pickup(APickupItem *item);
	void ToggleInventory();
	void MouseClicked();
	void Drop(UClass *className);

	// A map for the backpack
	TMap<FString, int> Backpack;
	// Individual maps for string name => Icon, Spell it casts, etc.
	TMap<FString, UTexture2D*> Icons;
	TMap<FString, UClass*> Classes;
	bool inventoryShowing;
};
