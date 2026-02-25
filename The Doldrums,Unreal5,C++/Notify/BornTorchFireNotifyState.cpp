// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/BornTorchFireNotifyState.h"
#include "Character/DDCharacterPlayer.h"
#include "Item/DDItemTorch.h"
#include "Niagara/DDFireActor.h"
#include <Animation/DDAnimInstance.h>


void UBornTorchFireNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	ADDCharacterPlayer* Pawn = Cast<ADDCharacterPlayer>(Owner);
	if (Pawn)
	{
		TArray<AActor*>Result;
		Pawn->GetOverlappingActors(Result, AActor::StaticClass());
		for (auto TmpActor : Result)
		{
			if (ADDFireActor* Fire = Cast<ADDFireActor>(TmpActor))
			{
				UWorld* World = MeshComp ? MeshComp->GetWorld() : nullptr;
				if (!ensure(World)) return;

				FVector Location = Pawn->EquipmentTorchPartC->GetComponentLocation();
				FRotator Rotation = Pawn->EquipmentTorchPartC->GetComponentRotation();

				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = MeshComp->GetOwner();
				SpawnParams.Instigator = Cast<APawn>(SpawnParams.Owner);
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				UClass* FireClass = FireActorBPClass ? FireActorBPClass.Get() : ADDFireActor::StaticClass();
				if (!ensure(FireClass)) return;

				FTransform SpawnTf(Rotation, Location, FVector(0.02f));
				AActor* SpawnedActor = World->SpawnActor<ADDFireActor>(FireClass, SpawnTf, SpawnParams);

				if (SpawnedActor && Pawn->EquipmentTorchPartC)
				{
					SpawnedActor->AttachToComponent(Pawn->EquipmentTorchPartC, FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("FireSocket"));




					Fire->ActivateFire();
				}



			}
		}
	}





}
