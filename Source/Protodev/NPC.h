// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class PROTODEV_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)

	FString npcMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)

	UTexture2D* npcIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)

	USphereComponent* ProxSphere;

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void Prox(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
