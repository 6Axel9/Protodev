#include "Protodev.h"
#include "Monster.h"
#include "Bullet.h"
#include "Avatar.h"

//========================================== Constructor
AMonster::AMonster()
{
	//========================================== Set Tick Every Frame
	PrimaryActorTick.bCanEverTick = true;
	//========================================== Speed
	Speed = 150;
	//========================================== HP
	HitPoints = 20;
	//========================================== Drop
	LootDropped = NULL;
	//========================================== Damage
	BaseAttackDamage = 1;
	//========================================== CoolDown
	AttackTimeout = 1.5f;
	//========================================== Timer
	TimeSinceLastStrike = 0;

	//========================================== Create Sub-Component
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	//========================================== Change To Root-Component
	RootComponent = CollisionBox;

	//========================================== Create Sub-Component
	SightRange = CreateDefaultSubobject<USphereComponent>(TEXT("SightSphere"));
	//========================================== Attach To Root (Default)
	SightRange->AttachToComponent(CollisionBox, FAttachmentTransformRules::KeepWorldTransform);

	//========================================== Create Sub-Component
	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("AttackSphere"));
	//========================================== Attach To Root (Default)
	AttackRange->AttachToComponent(CollisionBox, FAttachmentTransformRules::KeepWorldTransform);

	//========================================== Create Sub-Component
	ImpactParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Impact Particles"));
	//========================================== Attach To Root (Default)
	ImpactParticles->AttachToComponent(CollisionBox, FAttachmentTransformRules::KeepWorldTransform);

	//========================================== Sight Sphere On Trigger CallBack
	SightRange->OnComponentBeginOverlap.AddDynamic(this, &AMonster::ProxSight);
	//========================================== Attack Sphere On Trigger CallBack
	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &AMonster::ProxAttack);

	//========================================== Sight Sphere On Exit CallBack
	SightRange->OnComponentEndOverlap.AddDynamic(this, &AMonster::OutSight);
	//========================================== Attack Sphere On Exit CallBack
	AttackRange->OnComponentEndOverlap.AddDynamic(this, &AMonster::OutAttack);
}

//========================================== Initialize 
void AMonster::BeginPlay()
{
	//========================================== Call Parent Setup
	Super::BeginPlay();
	
}

//========================================== Update
void AMonster::Tick(float DeltaTime)
{
	//========================================== Call Parent Setup
	Super::Tick(DeltaTime);

	//========================================== Get Player Pawn As Avatar
	AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	//========================================== Get To Player Transformations
	FVector toPlayerDirection = FVector(avatar->GetActorLocation() - GetActorLocation());
	FRotator toPlayerRotation = FRotator(0.f, toPlayerDirection.Rotation().Yaw, toPlayerDirection.Rotation().Roll);
	toPlayerDirection.Normalize();

	//========================================== Rotate On Attack
	if (isInAttackRange)
	{
		RootComponent->SetWorldRotation(toPlayerRotation);
		//========================================== Atta Timer     
		TimeSinceLastStrike += DeltaTime;
		//========================================== Remove Message     
		if (TimeSinceLastStrike > AttackTimeout)
		{
			avatar->Damaged(this);
			TimeSinceLastStrike = 0.f;
		}
	}
	//========================================== Follow On Sight
	else if (isInSightRange)
	{
		RootComponent->SetWorldLocationAndRotation(GetActorLocation() + toPlayerDirection * Speed * DeltaTime, toPlayerRotation);
	}
}

//========================================== Inputs CallBacks
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//========================================== Call Parent Setup
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//========================================== Late Initialization
void AMonster::PostInitializeComponents()
{
	//========================================== Call Parent Setup
	Super::PostInitializeComponents();

}

void AMonster::ProxSight_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//========================================== Return If Not Avatar
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	//========================================== Avatar On Sight Range
	else
	{
		isInSightRange = true;
	}
}

void AMonster::ProxAttack_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//========================================== Return If Not Avatar
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	//========================================== Avatar On Attack Range
	else
	{
		isInAttackRange = true;
	}
}

void AMonster::OutSight_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	//========================================== Return If Not Avatar
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	//========================================== Avatar Exit From Sight Range
	else
	{
		isInSightRange = false;
	}
}

void AMonster::OutAttack_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	//========================================== Return If Not Avatar
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	//========================================== Avatar Exit From Attack Range
	else
	{
		isInAttackRange = false;
	}
}

void AMonster::Damaged(AActor* OtherActor)
{
	//========================================== Get Actor As Monster
	ABullet* bullet = Cast<ABullet>(OtherActor);
	//========================================== Damaged At Location
	ImpactParticles->SetWorldLocation(bullet->GetActorLocation());
	ImpactParticles->ActivateSystem();
	HitPoints -= bullet->Damage;
	//========================================== Destroy Object
	if (HitPoints < 0.f)
	{
		Destroy();
	}
}