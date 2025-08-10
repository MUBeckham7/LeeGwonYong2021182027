// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/AxingTreeNotifyState.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAxingTreeNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		return;
	}


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
