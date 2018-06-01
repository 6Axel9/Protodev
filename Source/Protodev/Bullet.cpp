#include "Protodev.h"
#include "Bullet.h"
#include "Monster.h"
#include "Interactive.h"

//========================================== Constructor
ABullet::ABullet()
{
	//========================================== Set Tick Every Frame
	PrimaryActorTick.bCanEverTick = true;
	//========================================== Damage
	Damage = 1;

	//========================================== Create Sub-Component
	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Proximity Sphere"));
	//========================================== Change To Root-Component
	RootComponent = ProxSphere;

	//========================================== Create Sub-Component
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	//========================================== Change To Root-Component
	StaticMesh->AttachToComponent(ProxSphere, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	ImpactParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Impact Particles"));
	//========================================== Attach To Root (Default)
	ImpactParticles->AttachToComponent(ProxSphere, FAttachmentTransformRules::KeepRelativeTransform);
	
	//========================================== Prox Sphere On Hit CallBack
	ProxSphere->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	//========================================== Particles Death CallBack
	ImpactParticles->OnSystemFinished.AddDynamic(this, &ABullet::OnFinish);

	//========================================== Create Sub-Component
	BulletAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BulletAudioComponent"));
	//========================================== Change To Root-Component
	BulletAudioComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BulletAudioComponent->bStopWhenOwnerDestroyed = false;
}

//========================================== Initialize 
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

//========================================== Update
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::OnHit_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	//========================================== Damaging Obstacles
	//AInteractive* obstacle = Cast<AInteractive>(OtherActor);
	//if (obstacle != nullptr)
	//{
	//	obstacle->Damaged(this, Damage);
	//}
	//========================================== Damaging Monster
	AMonster* monster = Cast<AMonster>(OtherActor);
	if (monster != nullptr)
	{
		monster->Damaged(this, Damage);
	}
	//========================================== Releasing Particles
	ImpactParticles->ActivateSystem();
	ImpactParticles->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	//========================================== Set Components Off
	StaticMesh->SetHiddenInGame(true);
	SetActorEnableCollision(false);

	//========================================== Play Audio
	if (BulletExplosionAudio) {
		//UGameplayStatics::PlaySoundAtLocation(this, BulletExplosionAudio, GetActorLocation());
		BulletAudioComponent->SetSound(BulletExplosionAudio);
		BulletAudioComponent->Play();
	}
}

void ABullet::OnFinish_Implementation(UParticleSystemComponent* PSystem)
{
	//========================================== Destroy On Particles Death
	Destroy();
}
