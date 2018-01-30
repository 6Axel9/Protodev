// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ObjectivesComponent.generated.h"

USTRUCT(BlueprintType)
struct FObjectivePart {
	GENERATED_BODY()

	TArray<bool> Completed;
	TArray<FString> PathDescription;

	void AddPath(FString Description) {
		PathDescription.Add(Description);
		Completed.Add(false);
	};
	void CompletePart() {
		Completed[0] = true;
	}
	void CompletePart(int Path) {
		Completed[Path - 1] = true;
	}
};

USTRUCT(BlueprintType)
struct FObjective {
	GENERATED_BODY()

	FString ObjectiveName;
	TArray<FObjectivePart*> Parts;
	bool Completed;

	void SetObjectiveName(FString Name) {
		ObjectiveName = Name;
	}
	void AddParts(int NumberOfParts) {
		for (int i = 0; i < NumberOfParts; i++) {
			Parts.Add(new FObjectivePart);
		}
	}
	void CompleteObjective() {
		Completed = true;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

	TArray<FObjective*> ListOfObjectives;
	FObjective* ContactStarfleet;

	void CreateContactStarfleetObjective();
	
	TArray<FObjective*>* GetList();
};
