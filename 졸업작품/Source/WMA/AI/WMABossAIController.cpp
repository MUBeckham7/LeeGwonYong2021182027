// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/WMABossAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "WMAAI.h"
#include <Perception/AIPerceptionComponent.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AISenseConfig_Hearing.h>
#include "AI/BTService_Detect.h"


AWMABossAIController::AWMABossAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/AI/Boss/BB_WMABoss.BB_WMABoss'"));
	if (nullptr != BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/Boss/BT_WMABoss.BT_WMABoss'"));
	if (nullptr != BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}

	SetPerceptionSystem();

	if (AIPerceptionComponent) {
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AWMABossAIController::OnTargetPerceptionUpdated);
	}
}



void AWMABossAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());

		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}

}

void AWMABossAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);		// 지금 동작하고 있는 BT 가져오기
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AWMABossAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//if (Actor && Actor->Tags.Contains("Player"))
	//{
	//	UBlackboardComponent* BlackboardPtr = GetBlackboardComponent();

	//	if (Stimulus.WasSuccessfullySensed())
	//	{
	//		// 플레이어 위치와 AI 위치 사이의 벡터 계산
	//		FVector Direction = Actor->GetActorLocation() - GetPawn()->GetActorLocation();
	//		Direction.Normalize();

	//		// AI 전방 벡터와 플레이어 위치 사이의 각도 계산
	//		float DotProduct = FVector::DotProduct(GetPawn()->GetActorForwardVector(), Direction);
	//		float Angle = FMath::Acos(DotProduct);
	//		float AngleDegrees = FMath::RadiansToDegrees(Angle);

	//		// 각도가 시야각 내에 있는지 확인
	//		if (AngleDegrees <= AISenseConfigSight->PeripheralVisionAngleDegrees / 2)
	//		{
	//			UE_LOG(LogTemp, Log, TEXT("InSight"));
	//			BlackboardPtr->SetValueAsObject(BBKEY_TARGET, Actor);
	//			BlackboardPtr->SetValueAsVector("LastKnownPosition", Actor->GetActorLocation());
	//		}
	//			// 성공적으로 감지된 경우
	//	}
	//		else
	//		{
	//			// 각도가 시야각 밖에 있는 경우
	//			HandleLostSight();
	//		}
	//}
	//else
	//{
	//		// 시각 자극을 감지하지 못한 경우
	//		HandleLostSight();
	//}

	auto SensedClass = UAIPerceptionSystem::GetSenseClassForStimulus(AISenseConfigHearing, Stimulus);
	UBlackboardComponent* BlackboardPtr = GetBlackboardComponent();

	if (Stimulus.WasSuccessfullySensed())
	{
		if (Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Hearing>())
		{
			const float Distance = FVector::Dist(Stimulus.ReceiverLocation, Stimulus.StimulusLocation);
			if (Distance < AISenseConfigHearing->HearingRange)
			{
				BlackboardPtr->SetValueAsObject(BBKEY_TARGET, Actor);
				//UE_LOG(LogTemp, Log, TEXT("Log Message : %f"), Distance);
			}
		}
	}
}


void AWMABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}

void AWMABossAIController::HandleLostSight()
{
	UBlackboardComponent* BlackboardPtr = GetBlackboardComponent();
	if (BlackboardPtr)
	{
		BlackboardPtr->ClearValue("TargetActor");
		BlackboardPtr->ClearValue("LastKnownPosition");
		// 추가적으로 해야 할 일이 있다면 여기에 구현합니다.
	}
}

void AWMABossAIController::SetPerceptionSystem()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("AI Sight config");
	AISenseConfigHearing = CreateDefaultSubobject<UAISenseConfig_Hearing>("AI Hearing config");

	SetPerceptionComponent(*CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception")));//

	AISenseConfigSight->SightRadius = 1200.0f;
	AISenseConfigSight->LoseSightRadius = 1700.0f;
	AISenseConfigSight->PeripheralVisionAngleDegrees = 180.0f;
	AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = true;

	//range 변경시 고쳐야함
	AISenseConfigHearing->HearingRange = 1200.0f;
	AISenseConfigHearing->LoSHearingRange = 1200.0f;
	AISenseConfigHearing->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigHearing->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfigHearing->DetectionByAffiliation.bDetectFriendlies = true;

	// Add the Sight Sense to the Perception Component
	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	AIPerceptionComponent->ConfigureSense(*AISenseConfigHearing);




}