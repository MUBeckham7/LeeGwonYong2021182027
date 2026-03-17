// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/DDGDTreeBase.h"
#include "DDNewPalmTree.generated.h"

class ADDPalm;

/**
 * 
 */

UCLASS()
class THEDOLDRUMS_API ADDNewPalmTree : public ADDGDTreeBase
{
	GENERATED_BODY()

public:
	ADDNewPalmTree(const FObjectInitializer& ObjInit);

protected:
	virtual void BeginPlay() override;

	virtual void HandleTreeFelled() override;
	void UpdatePalmGrowth();

	void GenerateRandomSpawnSchedule();
	void SpawnPalm();
	void FallFruit();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Palm")
	TSubclassOf<ADDPalm> PalmClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Palm")
	int32 MaxPalmPerYear = 12;

	UPROPERTY()
	int32 AccumulateDays = 0;

	UPROPERTY()
	float CurrentTime = 0.0f;

	UPROPERTY()
	float PreviousTime = -1.0f;

	UPROPERTY()
	int32 GeneratedThisYear = 0;

	UPROPERTY()
	TArray<int32> SpawnDays;

	TDoubleLinkedList<ADDPalm*> CoconutList;

	FTimerHandle PalmGrowthTimerHandle;

public:
	virtual void OnInteract() override;

};
