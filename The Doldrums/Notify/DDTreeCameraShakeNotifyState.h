// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DDTreeCameraShakeNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API UDDTreeCameraShakeNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
protected:

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
};
