// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "BornTorchFireNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API UBornTorchFireNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<class ADDFireActor> FireActorBPClass;
};
