// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_BossDetect.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API UBTService_BossDetect : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_BossDetect();
	bool bResult;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
