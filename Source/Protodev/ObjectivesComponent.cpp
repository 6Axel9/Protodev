// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "ObjectivesComponent.h"


// Sets default values for this component's properties
UObjectivesComponent::UObjectivesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectivesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	CreateContactStarfleetObjective();
}


// Called every frame
void UObjectivesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectivesComponent::CreateContactStarfleetObjective() {
	ContactStarfleet.SetObjectiveName("Contact the Starfleet to send a rescue ship.");
	ContactStarfleet.AddParts(3);
	ContactStarfleet.Parts[0]->AddPath("A: Locate and collect the ID from a randomized location within the compound grounds (not in the modular part of the base because the ID card unlocks the modular base).");
	ContactStarfleet.Parts[0]->AddPath("B: Use the ID card to access the modular base.");
	ContactStarfleet.Parts[1]->AddPath("A: Locate and collect the battery pack (from a randomized location).");
	ContactStarfleet.Parts[1]->AddPath("B: Locate the battery charger unit inside the mod-base and install the battery pack into it. This activates the big radar in the compound (cut-scene).");
	ContactStarfleet.Parts[2]->AddPath("A: Fend of large enemy waves for 1 min until the rescue ship arrives.");
	ContactStarfleet.Parts[2]->AddPath("B: Clear the infested landing pad.");
}
