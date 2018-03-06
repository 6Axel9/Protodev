// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "ObjectivesComponent.h"
#include "Objective.h"


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

	//StartContactStarfleetObjective();
	//StartResolveWarWithWordsObjective();
	//ContactStarfleet->Parts[0]->CompletePart();
}


// Called every frame
void UObjectivesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectivesComponent::StartContactStarfleetObjective() {
	/*ContactStarfleet = NewObject<UObjective>(this, UObjective::StaticClass());
	ContactStarfleet->SetObjectiveName("Contact the Starfleet to send a rescue ship");
	ContactStarfleet->AddParts(3);
	ContactStarfleet->Parts[0]->AddPath("A: Locate and collect the ID from a randomized location within the compound grounds");
	ContactStarfleet->Parts[0]->AddPath("B: Use the ID card to access the modular base");
	ContactStarfleet->Parts[1]->AddPath("A: Locate and collect the battery pack");
	ContactStarfleet->Parts[1]->AddPath("B: Locate the battery charger unit inside the mod-base and install the battery pack into it");
	ContactStarfleet->Parts[2]->AddPath("A: Fend of large enemy waves for 1 min until the rescue ship arrives");
	ContactStarfleet->Parts[2]->AddPath("B: Clear the infested landing pad");
	ListOfObjectives.Add(ContactStarfleet);*/
}

void UObjectivesComponent::StartResolveWarWithWordsObjective() {
	ResolveWarWithWords = NewObject<UObjective>(this, UObjective::StaticClass());
	ResolveWarWithWords->SetObjectiveName("Resolve the war with words");
	ResolveWarWithWords->NewPart("Use the ID card to access the modular base");
	ResolveWarWithWords->NewPart("Locate and collect the Hard Drive");
	ResolveWarWithWords->NewPart("Locate the Computer inside the mod-base and install the Hard Drive into it");
	ResolveWarWithWords->NewPart("Face-time the leader");
	ResolveWarWithWords->SetActivePart(ResolveWarWithWords->Parts[0]);
	/*ResolveWarWithWords->Parts[0]->AddPath("A: Locate and collect the ID from a randomized location within the compound grounds");
	ResolveWarWithWords->Parts[0]->AddPath("B: Use the ID card to access the modular base");
	ResolveWarWithWords->Parts[1]->AddPath("A: Locate and collect the Hard Drive");
	ResolveWarWithWords->Parts[1]->AddPath("B: Locate the Computer inside the mod-base and install the Hard Drive into it");
	ResolveWarWithWords->Parts[2]->AddPath("Face-time the leader");*/
	ListOfObjectives.Add(ResolveWarWithWords);
}

TArray<UObjective*> UObjectivesComponent::GetList() {
	return ListOfObjectives;
}

//FObjective UObjectivesComponent::GetList(int num) {
	//return ListOfObjectives[num - 1];
//}

//TArray<bool>* UObjectivesComponent::GetList2(){
	//return &testarray;
//}