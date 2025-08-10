// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/DDRotatingBranchNotifyState.h"
#include "Character/DDCharacterPlayer.h"
#include "Niagara/DDHeterogeneousSmokeComponent.h"
#include <Item/DDGeneratedDynamicMeshFlint.h>
#include "Niagara/DDFireActor.h"
#include <Animation/DDAnimInstance.h>


void UDDRotatingBranchNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AccumulatedTime = 0.f;
	RotationDirection = -1;
}

void UDDRotatingBranchNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		return;
	}

	AccumulatedTime += FrameDeltaTime;

	// 2) interval(��) ������ ���� ��ȯ
	if (AccumulatedTime >= SwitchInterval)
	{
		AccumulatedTime -= SwitchInterval;
		RotationDirection *= -1;
	}


	ADDCharacterPlayer* Pawn = Cast<ADDCharacterPlayer>(Owner);
	if (Pawn)
	{
		UStaticMeshComponent* Branch = Pawn->EquipmentBranch;
		if (!Branch) {
			return;
		}

		TArray<AActor*> Result;
		Pawn->GetOverlappingActors(Result, AActor::StaticClass());
		for (auto TmpActor : Result)
		{
			if (ADDGeneratedDynamicMeshFlint* Log = Cast<ADDGeneratedDynamicMeshFlint>(TmpActor))
			{
				const float DeltaYaw = RotationSpeed * FrameDeltaTime * RotationDirection;
				const FRotator DeltaRot(0.0f, 0.0f, DeltaYaw);

				Branch->AddLocalRotation(DeltaRot);

				

				if (Pawn->WheelCount == 10)
				{
					UDDHeterogeneousSmokeComponent* SmokeComp = Pawn->FindComponentByClass<UDDHeterogeneousSmokeComponent>();
					if (!SmokeComp)
					{
						UClass* SmokeClass = SmokeComponentBPClass
							? SmokeComponentBPClass.Get()
							: UDDHeterogeneousSmokeComponent::StaticClass();

						// ���� ������ ���� ������ Pawn�� ������Ʈ�� �߰�
						SmokeComp = NewObject<UDDHeterogeneousSmokeComponent>(Pawn, SmokeClass, TEXT("BranchSmokeComp"));
						SmokeComp->AttachToComponent(Branch, FAttachmentTransformRules::KeepRelativeTransform);
						SmokeComp->RegisterComponent();
						

					}
					SmokeComp->PlaySmoke();
				}

				if (Pawn->WheelCount > 20)
				{
					UWorld* World = MeshComp ? MeshComp->GetWorld() : nullptr;
					if (!ensure(World)) return;

					if (Log->SpawnedFireActor != nullptr)
					{
						return;
					}

					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = MeshComp->GetOwner();
					SpawnParams.Instigator = Cast<APawn>(SpawnParams.Owner);
					SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

					// 3) Ŭ���� ������ üũ
					UClass* FireClass = FireActorBPClass ? FireActorBPClass.Get() : ADDFireActor::StaticClass();
					if (!ensure(FireClass)) return;

					// 4) ���� ����
					FVector Location = Branch->GetComponentLocation();
					FRotator Rotation = FRotator::ZeroRotator;

					FTransform SpawnTf(Rotation, Location, FVector(0.02f));
					ADDFireActor* Fire = World->SpawnActor<ADDFireActor>(FireClass, SpawnTf,SpawnParams);

					Log->SpawnedFireActor = Fire;

					if (!ensure(Fire)) return;

					Pawn->ResetWheelCount();


					Fire->ActivateFire();

				}

			}
		}
	}
}
