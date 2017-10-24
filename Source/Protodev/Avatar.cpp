// Fill out your copyright notice in the Description page of Project Settings.

#include "Protodev.h"
#include "Avatar.h"


// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(InputComponent);

	InputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	InputComponent->BindAxis("Strafe", this, &AAvatar::MoveRight);
	InputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
	InputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);
	//InputComponent->BindAction("Jump", this, &AAvatar::Jumping);

}

void AAvatar::MoveForward(float amount)
{
	// Don't enter the body of this function if Controller is   // not set up yet, or if the amount to move is equal to 0   
	if( Controller && amount )
	{
		FVector fwd = GetActorForwardVector();
		// we call AddMovementInput to actually move the
		// player by `amount` in the `fwd` direction
		AddMovementInput(fwd, amount);
	}
}

void AAvatar::MoveRight(float amount)
{
	if (Controller && amount)
	{
		FVector right = GetActorRightVector();
		AddMovementInput(right, amount);
	}
}

void AAvatar::Yaw(float amount)
{
	AddControllerYawInput(50 * amount * GetWorld()->GetDeltaSeconds());

}

void AAvatar::Pitch(float amount)
{
	AddControllerPitchInput(50 * amount * GetWorld()->GetDeltaSeconds());
}

//void AAvatar::Jumping(bool keyheld)
//{
//	AAvatar::Jump();
//}
//
