// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DDItemDataAsset.generated.h"

UENUM(BlueprintType)
enum class EItemType :uint8
{
	None = 0,
	Branch = 1,
	WaterBottle,
	Food,
	ClothTShirt,
	ClothPants,
	ClothWatch,
	ClothBag,
	Axe,
	Torch,
	Machete,
};

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API UDDItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= Type)
	EItemType Type;

	UPROPERTY(EditDefaultsOnly, Category = Item)
	TSubclassOf<AActor> ItemActorClass;
	
};
