// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryActors/GeneratedDynamicMeshActor.h"
#include "DDGDTreeBase.generated.h"


class UBoxComponent;
class UWidgetComponent;
class UDynamicMeshComponent;
class UStaticMesh;
class UStaticMeshComponent;
class UUserWidget;
class USoundBase;
class ADDCharacterBase;

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API ADDGDTreeBase : public AGeneratedDynamicMeshActor
{
	GENERATED_BODY()
public:
	ADDGDTreeBase(const FObjectInitializer& ObjInit);

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void RebuildGeneratedMesh(UDynamicMesh* TargetMesh) override;

public:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepHitResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	virtual void OnInteract();

	UFUNCTION()
	virtual void SubtractWithTool(UStaticMeshComponent* ToolComponent, const FVector& ImpactWorldPoint);

protected:
	virtual void HandleTreeFelled();
	virtual void BuildStaticAttachments();
	virtual void ClearStaticAttachments();

	void TickFalling();
	void SetupInteractionWidget();
	void ApplySourceMeshToDynamicMesh(UDynamicMesh* TargetMesh);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree")
	TObjectPtr<USceneComponent> TreeRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree")
	TObjectPtr<UBoxComponent> TriggerTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree")
	TObjectPtr<UWidgetComponent> Text;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree")
	TArray<TObjectPtr<UStaticMeshComponent>> StaticAttachments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree|Mesh")
	TObjectPtr<UStaticMesh> TrunkMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree|Mesh")
	TArray<TObjectPtr<UStaticMesh>> AttachmentMeshes;

	UPROPERTY()
	TObjectPtr<UDynamicMesh> TargetMeshResult;

	UPROPERTY()
	TObjectPtr<ADDCharacterBase> CachedPlayer;

	UPROPERTY()
	TObjectPtr<AActor> PlayerActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree|UI")
	TSubclassOf<UUserWidget> InteractionItemWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> ItemWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree|Chop")
	int32 HitsToBreak = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree|Chop")
	float ShakeStrength = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree|Chop")
	float ShakeDuration = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree|Fall")
	float FallAngle = 98.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree|Fall")
	float FallDuration = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree|Fall")
	float FallInterval = 0.02f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree|Fall")
	TObjectPtr<USoundBase> FallSound;

	int32 CurrentHits = 0;
	float FallElapsedTime = 0.0f;
	FRotator FallStartRot;
	FRotator FallEndRot;
	FTimerHandle FallTimerHandle;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tree")
	TObjectPtr<UDynamicMeshComponent> DynamicMeshComp;

};
