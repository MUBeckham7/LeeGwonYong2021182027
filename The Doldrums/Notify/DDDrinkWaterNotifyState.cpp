// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/DDDrinkWaterNotifyState.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UDDDrinkWaterNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

    AActor* Owner = MeshComp->GetOwner();
    ACharacter* Character = Cast<ACharacter>(Owner);
    if (!Character)
    {
        return;
    }

    if (Character->GetCharacterMovement())
    {
        Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
    }
}
