// Fill out your copyright notice in the Description page of Project Settings.

#include "GoldenEgg.h"
#include "Monster.h"
#include "Avatar.h"
#include "MeleeWeapon.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 20;
	HitPoints = 20;
	Experience = 0;
	LootDropped = NULL;
	BaseAttackDamage = 1;
	AttackTimeout = 1.5f;
	TimeSinceLastStrike = 0;
	SightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SightSphere"));
	SightSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRangeSphere"));
	AttackRangeSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!avatar) return;

	FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();
	float DistanceToPlayer = toPlayer.Size();
	toPlayer.Normalize();
	

	if (isInSightRange(DistanceToPlayer)) {
		AddMovementInput(toPlayer, Speed*DeltaTime);

		FRotator toPlayerRotation = toPlayer.Rotation();
		toPlayerRotation.Pitch = 0;
		RootComponent->SetWorldRotation(toPlayerRotation);
	}
	/*float test = SightSphere->GetScaledSphereRadius();
	FString TheFloatStr = FString::SanitizeFloat(test);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::White, TheFloatStr);*/
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (BPMeleeWeapon)
	{
		MeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(BPMeleeWeapon, FVector(), FRotator());
		if (MeleeWeapon)
		{
			const USkeletalMeshSocket* socket = GetMesh()->GetSocketByName("weaponSocket");
			//const UStaticMeshSocket* socket2 = MeleeWeapon->GetRootComponent()->getsocketb
			socket->AttachActor(MeleeWeapon, GetMesh());
		}
	}
}