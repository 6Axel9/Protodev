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
	ContactStarfleet = NewObject<UObjective>(this, UObjective::StaticClass());
	ContactStarfleet->SetObjectiveName("Contact the Starfleet to send a rescue ship");
	ContactStarfleet->NewPart("Use the ID card to access the base");
	ContactStarfleet->NewPart("Locate and collect the Battery Pack");
	ContactStarfleet->NewPart("Locate the battery charger unit inside the mod-base and install the battery pack into it");
	ContactStarfleet->NewPart("Fend of large enemy waves for 1 minute");
	ContactStarfleet->NewPart("Clear the infested landing pad");
	ContactStarfleet->NewPart("Get in the rescue ship");
	ContactStarfleet->SetActivePart(ContactStarfleet->Parts[0]);
	ListOfObjectives.Add(ContactStarfleet);
}

void UObjectivesComponent::StartKillAllEnemiesObjective(){
	KillAllEnemies = NewObject<UObjective>(this, UObjective::StaticClass());
	KillAllEnemies->SetObjectiveName("Kill all enemies from the start");
	KillAllEnemies->NewPart("Kill the Boss");
	KillAllEnemies->NewPart("Wait for the rescue ship to arrive");
	KillAllEnemies->NewPart("Get in the rescue ship");
	KillAllEnemies->SetActivePart(KillAllEnemies->Parts[0]);
	ListOfObjectives.Add(KillAllEnemies);
}

void UObjectivesComponent::StartResolveWarWithWordsObjective() {
	ResolveWarWithWords = NewObject<UObjective>(this, UObjective::StaticClass());
	ResolveWarWithWords->SetObjectiveName("Resolve the war with words");
	ResolveWarWithWords->NewPart("Use the ID card to access the base");
	ResolveWarWithWords->NewPart("Locate and collect the Hard Drive");
	ResolveWarWithWords->NewPart("Locate the Computer inside the mod-base and install the Hard Drive into it");
	ResolveWarWithWords->NewPart("Face-time the leader");
	ResolveWarWithWords->SetActivePart(ResolveWarWithWords->Parts[0]);
	ListOfObjectives.Add(ResolveWarWithWords);
}

void UObjectivesComponent::StartFindAPrototypeWeaponObjective(){
	FindAPrototypeWeapon = NewObject<UObjective>(this, UObjective::StaticClass());
	FindAPrototypeWeapon->SetObjectiveName("Find a prototype weapon and destroy the enemy lair");
	FindAPrototypeWeapon->NewPart("Locate the data display unit and upload the data into it");
	FindAPrototypeWeapon->NewPart("Locate the storage container and type in the code");
	FindAPrototypeWeapon->NewPart("Destroy the enemy lair with the weapon");
	FindAPrototypeWeapon->SetActivePart(FindAPrototypeWeapon->Parts[0]);
	ListOfObjectives.Add(FindAPrototypeWeapon);
}

void UObjectivesComponent::StartFixYourShipObjective(){
	FixYourShip = NewObject<UObjective>(this, UObjective::StaticClass());
	FixYourShip->SetObjectiveName("Fix your ship and fly off");
	FixYourShip->NewPart("Use the ID card to access the base");
	FixYourShip->NewPart("Locate and collect the Duct Tape and Flux Capacitor");
	FixYourShip->NewPart("Locate and collect the Screwdriver and Repair Book");
	FixYourShip->NewPart("Leave the Compound and get back to your ship");
	FixYourShip->NewPart("Use the items to fix the ship");
	FixYourShip->NewPart("Escape the planet in the restored ship");
	FixYourShip->SetActivePart(FixYourShip->Parts[0]);
	ListOfObjectives.Add(FixYourShip);
}

void UObjectivesComponent::StartInfectTheBugsObjective(){
	InfectTheBugs = NewObject<UObjective>(this, UObjective::StaticClass());
	InfectTheBugs->SetObjectiveName("Infect the bugs with a virus");
	InfectTheBugs->NewPart("Use the Power Cell to access the Restricted Area");
	InfectTheBugs->NewPart("Pick up the Virus from the Restricted Area");
	InfectTheBugs->NewPart("Locate and collect the Water Rifle");
	InfectTheBugs->NewPart("Combine the Virus with the Water Rifle");
	InfectTheBugs->NewPart("Fire the Water Rifle over the Compound Walls to infect the aliens");
	InfectTheBugs->SetActivePart(InfectTheBugs->Parts[0]);
	ListOfObjectives.Add(InfectTheBugs);
}

void UObjectivesComponent::StartPooOnAStickObjective(){
	PooOnAStick = NewObject<UObjective>(this, UObjective::StaticClass());
	PooOnAStick->SetObjectiveName("Poo on a stick");
	PooOnAStick->NewPart("Use the ID card to access the base");
	PooOnAStick->NewPart("Locate and collect the Stick");
	PooOnAStick->NewPart("Locate and collect the Screwdriver");
	PooOnAStick->NewPart("Use the Screwdriver to crank open the toi-toi door");
	PooOnAStick->NewPart("Collect the poo from the toi-toi");
	PooOnAStick->NewPart("Combine the poo with the stick");
	PooOnAStick->SetActivePart(PooOnAStick->Parts[0]);
	ListOfObjectives.Add(PooOnAStick);
}

void UObjectivesComponent::StartEscapeInTheSecretShipObjective(){
	EscapeInTheSecretShip = NewObject<UObjective>(this, UObjective::StaticClass());
	EscapeInTheSecretShip->SetObjectiveName("Escape in the secret ship");
	EscapeInTheSecretShip->NewPart("Use the Cloaking Device Controller near to the Landing Pad");
	EscapeInTheSecretShip->NewPart("The ship is missing a Hyperdrive, locate and collect it");
	EscapeInTheSecretShip->NewPart("Return to the landing pad");
	EscapeInTheSecretShip->NewPart("Kill the final wave of enemies");
	EscapeInTheSecretShip->SetActivePart(EscapeInTheSecretShip->Parts[0]);
	ListOfObjectives.Add(EscapeInTheSecretShip);
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