// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryActors/GeneratedDynamicMeshActor.h"
#include <Character/DDCharacterBase.h>
#include "DDGeneratedDynamicMeshFlint.generated.h" 

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API ADDGeneratedDynamicMeshFlint : public AGeneratedDynamicMeshActor
{
	GENERATED_BODY()


public:

	ADDGeneratedDynamicMeshFlint(const FObjectInitializer& ObjInit);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Mesh")
	TObjectPtr<class UStaticMesh> LogMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<class UDynamicMeshComponent> DynamicMeshComp;

	UPROPERTY()
	UDynamicMesh* TargetMeshResult;

	UPROPERTY()
	ADDCharacterBase* OverlappingChar;

	virtual void OnConstruction(const FTransform& Transform) override;

public:

	virtual void RebuildGeneratedMesh(UDynamicMesh* TargetMesh)override;

	UFUNCTION()
	void OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void SubtractWithTool(UStaticMeshComponent* ToolComponent, const FVector& ImpactWorldPoint);

	UPROPERTY()
	TObjectPtr<class ADDFireActor> SpawnedFireActor = nullptr;


};
