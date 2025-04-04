// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionTypes.h"
#include "WMABossAIController.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API AWMABossAIController : public AAIController
{
	GENERATED_BODY()
public:
	AWMABossAIController();

	void RunAI();
	void StopAI();

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

protected:
	virtual void OnPossess(APawn* InPawn) override;

	AActor* PerceivedActor;

	UFUNCTION()
	void HandleLostSight();

	FTimerHandle LostSightTimerHandle;

private:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;

	UPROPERTY(EditAnywhere, Category = "AI Perception")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent = nullptr;
	TObjectPtr<class UAISenseConfig_Sight> AISenseConfigSight = nullptr;
	TObjectPtr<class UAISenseConfig_Hearing> AISenseConfigHearing = nullptr;


	void SetPerceptionSystem();
};
