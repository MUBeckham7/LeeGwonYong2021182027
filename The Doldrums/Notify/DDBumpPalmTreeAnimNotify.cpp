// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/DDBumpPalmTreeAnimNotify.h"
#include "Character/DDCharacterPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "DDBumpPalmTreeAnimNotify.h"



void UDDBumpPalmTreeAnimNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		return;
	}


	ADDCharacterPlayer* Pawn = Cast<ADDCharacterPlayer>(Owner);
	if (Pawn && Pawn->GetController())
	{
		Pawn->GetController()->ResetIgnoreLookInput();
		//Pawn->RetrunTodefaultView();
		Pawn->bIsReturningToDefaultRotation = true;
		

	}
	//ADDPalmTree* Palm = Cast<ADDPalmTree>(Owner);
	//if (Palm && Palm->Fruit)
	//{
	//	UE_LOG(LogTemp,Log,TEXT("FUCCCCK!"))
	//	UStaticMeshComponent* FruitComponent = Palm->Fruit;
	//	FruitComponent->SetSimulatePhysics(true);
	//	FruitComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	//	FruitComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//}

	UCapsuleComponent* CapsuleComp = Owner->FindComponentByClass<UCapsuleComponent>();

	if (CapsuleComp)
	{
		TArray<UPrimitiveComponent*> OverlappingComponents;
		CapsuleComp->GetOverlappingComponents(OverlappingComponents);

		for (UPrimitiveComponent* OverlapComp : OverlappingComponents)
		{
			if (OverlapComp)
			{
				UE_LOG(LogTemp, Log, TEXT("Overlapping component: %s"), *OverlapComp->GetName());

				TArray<USceneComponent*> ChildComps;
				OverlapComp->GetChildrenComponents(true, ChildComps);
				for (USceneComponent* Child : ChildComps)
				{
					// Fruit가 UStaticMeshComponent라면 캐스팅
					UStaticMeshComponent* FruitMesh = Cast<UStaticMeshComponent>(Child);
					if (FruitMesh && FruitMesh->GetName().Contains(TEXT("Fruit")))
					{
						// 물리 시뮬레이션 켜기
						FruitMesh->SetSimulatePhysics(true);
						// 필요 시 분리 (부모로부터 Detach)
						FruitMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
						// 충돌 활성화
						FruitMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					}
				}


			}
		}
	}



}
