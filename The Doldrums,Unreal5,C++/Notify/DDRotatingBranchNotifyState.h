 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DDRotatingBranchNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API UDDRotatingBranchNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "BranchRotation")
	float RotationSpeed = 180.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BranchRotation")
	float SwitchInterval = 0.45f;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp,UAnimSequenceBase* Animation,float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<class ADDFireActor> FireActorBPClass;

	UPROPERTY(EditAnywhere, Category = "Notify|Smoke")
	TSubclassOf<class UDDHeterogeneousSmokeComponent> SmokeComponentBPClass;

private:
	/** 누적된 시간 */
	float AccumulatedTime = 0.f;

	/** 현재 회전 방향 (1 = 시계, -1 = 반시계) */
	int32 RotationDirection = 1;

};
