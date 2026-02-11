// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DDAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UDDAnimInstance::UDDAnimInstance()
{
	MovingThreshould = 3.0f;
	JumpingThreshould = 5.0f;
}

void UDDAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();


	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UDDAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);
	}

}

void UDDAnimInstance::CharacterWalk()
{
	Movement->MaxWalkSpeed = 220.0f;
	GroundSpeed = 220.0f;
	UE_LOG(LogTemp, Log, TEXT("Relase SHIFT"));

}

void UDDAnimInstance::CharacterRun()
{
	Movement->MaxWalkSpeed = 480.0f;
	GroundSpeed = 480.0f;
	UE_LOG(LogTemp, Log, TEXT("Hold SHIFT"));
}
