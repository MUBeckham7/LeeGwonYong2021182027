// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/DDBumpPalmTreeAnimNotify.h"
#include "Character/DDCharacterPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Prop/DDPalmTree.h"



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

	if (Pawn)
	{
		TArray<AActor*>Result;
		Pawn->GetOverlappingActors(Result, AActor::StaticClass());
		for (auto TmpActor : Result)
		{
			if (ADDPalmTree* PalmTree = Cast<ADDPalmTree>(TmpActor))
			{
				PalmTree->FallFruit();
			}
		}
	}

}
