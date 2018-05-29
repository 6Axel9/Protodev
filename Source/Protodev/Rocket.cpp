// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Rocket.h"
#include "Monster.h"
#include "Interactive.h"

//========================================== Constructor
ARocket::ARocket()
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
	DamageSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Damage Mesh"));
	//========================================== Change To Root-Component
	DamageSphere->AttachToComponent(ProxSphere, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Create Sub-Component
	ImpactParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Impact Particles"));
	//========================================== Attach To Root (Default)
	ImpactParticles->AttachToComponent(ProxSphere, FAttachmentTransformRules::KeepRelativeTransform);

	//========================================== Prox Sphere On Hit CallBack
	ProxSphere->OnComponentHit.AddDynamic(this, &ARocket::OnHit);
	//========================================== Damage Sphere On Overlap CallBack
	DamageSphere->OnComponentBeginOverlap.AddDynamic(this, &ARocket::BeginOverlap);
	DamageSphere->OnComponentEndOverlap.AddDynamic(this, &ARocket::EndOverlap);
	//========================================== Particles Death CallBack
	ImpactParticles->OnSystemFinished.AddDynamic(this, &ARocket::OnFinish);

	//========================================== Create Sub-Component
	BulletAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BulletAudioComponent"));
	//========================================== Change To Root-Component
	BulletAudioComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BulletAudioComponent->bStopWhenOwnerDestroyed = false;
}

//========================================== Initialize 
void ARocket::BeginPlay()
{
	Super::BeginPlay();
}

//========================================== Update
void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARocket::OnHit_Implementation(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	//========================================== Handle Damage
	for (int i = 0; i < OverlappedTargets.Num(); i++) {
		/*if (Cast<AInteractive>(OverlappedTargets[i])) {
			FVector rightdirection = (FVector::CrossProduct(OverlappedTargets[i]->GetActorLocation(), GetActorLocation()) * -1);
			Cast<AInteractive>(OverlappedTargets[i])->CollisionBox->AddImpulse(rightdirection * ((DamageSphere->GetScaledSphereRadius() / FVector::Distance(StaticMesh->GetComponentLocation(), OverlappedTargets[i]->GetActorLocation())) / 200));
			Cast<AInteractive>(OverlappedTargets[i])->Damaged(this, CalculateDamage(DamageSphere->GetScaledSphereRadius(), FVector::Distance(StaticMesh->GetComponentLocation(), OverlappedTargets[i]->GetActorLocation())));
		}*/
		if (Cast<AMonster>(OverlappedTargets[i])) {
			FVector rightdirection = (FVector::CrossProduct(OverlappedTargets[i]->GetActorLocation(), GetActorLocation()) * -1);
			Cast<AMonster>(OverlappedTargets[i])->CollisionBox->AddImpulse(rightdirection * ((DamageSphere->GetScaledSphereRadius() / FVector::Distance(StaticMesh->GetComponentLocation(), OverlappedTargets[i]->GetActorLocation())) / 200));
			Cast<AMonster>(OverlappedTargets[i])->Damaged(this, CalculateDamage(DamageSphere->GetScaledSphereRadius(), FVector::Distance(StaticMesh->GetComponentLocation(), OverlappedTargets[i]->GetActorLocation())));
		}
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

void ARocket::BeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {
	if (Cast<AInteractive>(OtherActor) || Cast<AMonster>(OtherActor)) {
		OverlappedTargets.Add(OtherActor);
	}
}

void ARocket::EndOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (Cast<AInteractive>(OtherActor) || Cast<AMonster>(OtherActor)) {
		OverlappedTargets.Remove(OtherActor);
	}
}

void ARocket::OnFinish_Implementation(UParticleSystemComponent* PSystem)
{
	//========================================== Destroy On Particles Death
	Destroy();
}

float ARocket::CalculateDamage(float DamageRadius, float TargetDistance) {
	if (DamageRadius / TargetDistance > 1) {
		return Damage;
	}
	else {
		return (DamageRadius / TargetDistance) * Damage;
	}
}