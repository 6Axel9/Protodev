// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ObjectivesComponent.generated.h"

UCLASS(BlueprintType)
class PROTODEV_API UObjectivesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectivesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<class UObjective*> ListOfObjectives;
	class UObjective* ContactStarfleet;
	class UObjective* KillAllEnemies;
	class UObjective* ResolveWarWithWords;
	class UObjective* FindAPrototypeWeapon;
	class UObjective* FixYourShip;
	class UObjective* InfectTheBugs;
	class UObjective* PooOnAStick;
	class UObjective* EscapeInTheSecretShip;

	void StartContactStarfleetObjective();
	void StartKillAllEnemiesObjective();
	void StartResolveWarWithWordsObjective();
	void StartFindAPrototypeWeaponObjective();
	void StartFixYourShipObjective();
	void StartInfectTheBugsObjective();
	void StartPooOnAStickObjective();
	void StartEscapeInTheSecretShipObjective();
	UFUNCTION(BlueprintCallable)
		TArray<UObjective*> GetList();
	//UFUNCTION(BlueprintCallable)
		//TArray<bool>* GetList2();
	//FObjective GetList(int num);
};
