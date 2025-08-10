// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DDDrinkWaterNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API UDDDrinkWaterNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	

protected:

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
};
