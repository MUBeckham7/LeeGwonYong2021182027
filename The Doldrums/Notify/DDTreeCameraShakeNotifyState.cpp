// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/DDTreeCameraShakeNotifyState.h"
#include "Character/DDCharacterPlayer.h"


void UDDTreeCameraShakeNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration);

    AActor* Owner = MeshComp->GetOwner();
    if (!Owner)
    {
        return;
    }


    ADDCharacterPlayer* Pawn = Cast<ADDCharacterPlayer>(Owner);
    if (Pawn)
    {
        // Pawn이 소유한 컨트롤러를 안전하게 캐스트
        if (APlayerController* PC = Cast<APlayerController>(Pawn->GetController()))
        {
            if (Pawn->AxingTreeCameraShake)
            {
                UE_LOG(LogTemp, Log, TEXT("Starting Camera Shake"));
                PC->ClientStartCameraShake(Pawn->AxingTreeCameraShake);
            }
        }
    }

}
