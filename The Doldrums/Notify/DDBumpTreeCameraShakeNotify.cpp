// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/DDBumpTreeCameraShakeNotify.h"
#include "Character/DDCharacterPlayer.h"


void UDDBumpTreeCameraShakeNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
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
        // Pawn�� ������ ��Ʈ�ѷ��� �����ϰ� ĳ��Ʈ
        if (APlayerController* PC = Cast<APlayerController>(Pawn->GetController()))
        {
            if (Pawn->BumpTreeCameraShake)
            {
                UE_LOG(LogTemp, Log, TEXT("Starting Camera Shake"));
                PC->ClientStartCameraShake(Pawn->BumpTreeCameraShake);
            }
        }
    }
}
