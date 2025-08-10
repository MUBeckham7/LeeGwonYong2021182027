// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryActors/GeneratedDynamicMeshActor.h"
#include "DDGeneratedDynamicMeshActorLog.generated.h"

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API ADDGeneratedDynamicMeshActorLog : public AGeneratedDynamicMeshActor
{
	GENERATED_BODY()

public:

	ADDGeneratedDynamicMeshActorLog(const FObjectInitializer& ObjInit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<class UStaticMesh> LogMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<class UDynamicMeshComponent> DynamicMeshComp;

	UPROPERTY()
	UDynamicMesh* TargetMeshResult;

	UPROPERTY()
	TObjectPtr<class ADDCharacterBase> OverlappingChar;

	virtual void OnConstruction(const FTransform& Transform) override;

public:

	virtual void RebuildGeneratedMesh(UDynamicMesh* TargetMesh)override;

	UFUNCTION()
	void OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void SubtractWithTool(UStaticMeshComponent* ToolComponent, const FVector& ImpactWorldPoint);

protected:
    // 한 번 베일 때마다 +1, HitsToBreak 번 베이면 나무가 넘어갑니다
	UPROPERTY(EditAnywhere, Category = "Chop")
	int32 HitsToBreak = 5;

	/** 현재까지 베인 횟수 */
	int32 CurrentHits = 0;

	/** 흔들림 세기(월드 단위) */
	UPROPERTY(EditAnywhere, Category = "Chop")
	float ShakeStrength = 0.3f;

	/** 흔들림 지속 시간(초) */
	UPROPERTY(EditAnywhere, Category = "Chop")
	float ShakeDuration = 0.1f;

	FTimerHandle FallTimerHandle;
	// 회전 애니메이션 제어용
	FRotator FallStartRot;
	FRotator FallEndRot;
	float   FallAngle = 98.f;   // 쓰러질 총 각도
	float   FallDuration = 3.0f;     // 쓰러질 시간
	float   FallInterval = 0.02f;    // 타이머 틱 간격
	float   FallElapsedTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Chop|Sound")
	USoundBase * FallSound;

	// 타이머 콜백
	void TickFalling();

};
