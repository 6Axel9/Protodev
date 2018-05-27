#include "Protodev.h"
#include "Monster.h"
#include "EngineUtils.h"



//========================================== Constructor
AMonster::AMonster()
{
	needs_range = true;

	//========================================== Set Tick Every Frame
	PrimaryActorTick.bCanEverTick = true;
	//========================================== Speed
	RotationSpeed = 5.f;
	//========================================== Speed
	MovementSpeed = 500.f;
	//========================================== HP
	HitPoints = 20.f;
	//========================================== Drop
	LootDropped = NULL;
	//========================================== Damage
	BaseAttackDamage = 1.f;
	//========================================== CoolDown
	AttackTimeout = 1.5f;
	//========================================== Timer
	TimeSinceLastStrike = 0.f;


	//========================================== Create Sub-Component
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	//========================================== Change To Root-Component
	RootComponent = CollisionBox;

	//========================================== Create Sub-Component
	deadAntMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DeadMesh"));
	//========================================== Change To Root-Component
	deadAntMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	SightRange = CreateDefaultSubobject<USphereComponent>(TEXT("SightSphere"));
	//========================================== Attach To Root (Default)
	SightRange->AttachToComponent(CollisionBox, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("AttackSphere"));
	//========================================== Attach To Root (Default)
	AttackRange->AttachToComponent(CollisionBox, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Sight Sphere On Trigger CallBack
	SightRange->OnComponentBeginOverlap.AddDynamic(this, &AMonster::ProxSight);
	//========================================== Attack Sphere On Trigger CallBack
	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &AMonster::ProxAttack);

	//========================================== Sight Sphere On Exit CallBack
	SightRange->OnComponentEndOverlap.AddDynamic(this, &AMonster::OutSight);
	//========================================== Attack Sphere On Exit CallBack
	AttackRange->OnComponentEndOverlap.AddDynamic(this, &AMonster::OutAttack);

	deadAntMesh->SetHiddenInGame(true);

	needs_range = true;
}

//========================================== Initialize 
void AMonster::BeginPlay()
{
	//========================================== Call Parent Setup
	Super::BeginPlay();

	//========================================== Get Player Pawn As Avatar
	avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


}

//========================================== Update
void AMonster::Tick(float DeltaTime)
{
	//========================================== Call Parent Setup
	Super::Tick(DeltaTime);

	//========================================== Get To Player Transformations
	if (!needs_death) //do your math only if you need
	{
		FVector toPlayerDirection = avatar->GetActorLocation() - GetActorLocation();

		FVector desired_direction = FVector(0);
		FRotator desired_rotation = FRotator(0);


		float distance = toPlayerDirection.Size();
		float deceleration = distance / 50.f;

		float new_speed = MovementSpeed * deceleration;


		//========================================== Rotate On Attack
		if (isInAttackRange)
		{
			isMoving = false;

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
		else if (isInSightRange || !needs_range)
		{

			toPlayerDirection.Normalize();
			desired_direction = toPlayerDirection * (new_speed * DeltaTime);

			desired_direction.Normalize();
			desired_rotation = desired_direction.Rotation();

			RootComponent->SetWorldRotation(desired_rotation);

			RootComponent->AddWorldOffset(toPlayerDirection * MovementSpeed * DeltaTime);
			RootComponent->SetWorldRotation(FMath::Lerp(GetActorQuat(), desired_rotation.Quaternion(), RotationSpeed * DeltaTime));
		}
		//========================================== Always aim for the gate otherwhise
		if (!isInSightRange && needs_range)
		{
			FVector _target = FVector(0);

			//========================================== Get Gate Object from the World
			for (TActorIterator<AMainGate> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				gate = *ActorItr;
				_target = gate->GetActorLocation();
				if (gate->open)
				{
					needs_range = false;
				}
			}

			FVector toGateDirection = _target - GetActorLocation();


			isMoving = true;

			toGateDirection.Normalize();
			desired_direction = toGateDirection * (new_speed * DeltaTime);

			desired_direction.Normalize();
			desired_rotation = desired_direction.Rotation();

			RootComponent->SetWorldRotation(desired_rotation);
			
			RootComponent->AddWorldOffset(toGateDirection * MovementSpeed * DeltaTime);
			RootComponent->SetWorldRotation(FMath::Lerp(GetActorQuat(), desired_rotation.Quaternion(), RotationSpeed * DeltaTime));
		}
	}

	if (needs_death)
	{
		time_since_dead += DeltaTime;
		deadAntMesh->SetHiddenInGame(false);
		deadAntMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

		needs_range = true;

		if (time_since_dead > 10 )
		{
			needs_death = false;
			Destroy();
		}
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

bool AMonster::GetNeedsToDie()
{
	return needs_death;
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
	HitPoints -= bullet->Damage;
	//========================================== Destroy Object
	if (HitPoints < 0.f)
	{
		TArray<USkeletalMeshComponent*> Components;
		this->GetComponents<USkeletalMeshComponent>(Components);
		for (int32 i = 0; i<Components.Num(); i++) //Count is zero
		{
			USkeletalMeshComponent* SkeletalMeshComponent = Components[i]; //null
			SkeletalMeshComponent->SetHiddenInGame(true);
		}

		needs_death = true;
	}
}