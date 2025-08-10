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
    // �� �� ���� ������ +1, HitsToBreak �� ���̸� ������ �Ѿ�ϴ�
	UPROPERTY(EditAnywhere, Category = "Chop")
	int32 HitsToBreak = 5;

	/** ������� ���� Ƚ�� */
	int32 CurrentHits = 0;

	/** ��鸲 ����(���� ����) */
	UPROPERTY(EditAnywhere, Category = "Chop")
	float ShakeStrength = 0.3f;

	/** ��鸲 ���� �ð�(��) */
	UPROPERTY(EditAnywhere, Category = "Chop")
	float ShakeDuration = 0.1f;

	FTimerHandle FallTimerHandle;
	// ȸ�� �ִϸ��̼� �����
	FRotator FallStartRot;
	FRotator FallEndRot;
	float   FallAngle = 98.f;   // ������ �� ����
	float   FallDuration = 3.0f;     // ������ �ð�
	float   FallInterval = 0.02f;    // Ÿ�̸� ƽ ����
	float   FallElapsedTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Chop|Sound")
	USoundBase * FallSound;

	// Ÿ�̸� �ݹ�
	void TickFalling();

};
