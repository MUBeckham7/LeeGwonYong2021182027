// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/WoodSubtractToolNotifyState.h"
#include "Character/DDCharacterPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

void UWoodSubtractToolNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp)
	{
		AActor* Owner = MeshComp->GetOwner();

		if (ADDCharacterPlayer* Player = Cast<ADDCharacterPlayer>(Owner))
		{
			Player->AxeAction();

			if (ChopSound)
			{
				UGameplayStatics::PlaySoundAtLocation(Player->GetWorld(), ChopSound, Player->GetActorLocation());
			}

		}
	}


}
