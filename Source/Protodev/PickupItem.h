// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

class AGUI;

UCLASS()
class PROTODEV_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItem();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// The name of the item you are getting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		FString Name;

	// How much you are getting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		int32 Quantity;

	// the sphere you collide with to pick item up
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
		USphereComponent* ProxSphere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
		UStaticMeshComponent* Mesh;

	// The icon that represents the object in UI/canvas
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		UTexture2D* Icon;

	UFUNCTION(BlueprintNativeEvent, Category = Item)
	void Prox(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//void Prox(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
