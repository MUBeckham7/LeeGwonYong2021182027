// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/DDBornFireNotifyState.h"
#include "Character/DDCharacterPlayer.h"

void UDDBornFireNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		return;
	}

	ADDCharacterPlayer* Pawn = Cast<ADDCharacterPlayer>(Owner);
	if (Pawn)
	{
		
		Pawn->EquipmentBranch->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		//Pawn->Equipment->SetSimulatePhysics(true);

		

		Pawn->EquipmentBranch->AttachToComponent(Pawn->GetMesh(),FAttachmentTransformRules::KeepWorldTransform , TEXT("VB_BornFireSocket"));
	}

	ElapsedRotateTime = 0.0f;
}

