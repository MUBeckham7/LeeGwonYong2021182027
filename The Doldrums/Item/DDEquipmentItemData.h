// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/DDItemDataAsset.h"
#include "DDEquipmentItemData.generated.h"

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API UDDEquipmentItemData : public UDDItemDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,Category= Equipment)
	TSoftObjectPtr<USkeletalMesh> EquipmentSkeltalMesh;

	UPROPERTY(EditAnywhere, Category = Equipment)
	TSoftObjectPtr<USkeletalMesh> EquipmentSkeltalMesh2;

	//UPROPERTY(EditAnywhere, Category = Equipment)
	//TSoftObjectPtr<UStaticMesh> EquipmentStaticMesh;

	UPROPERTY(EditAnywhere, Category = Equipment)
	TSoftObjectPtr<UStaticMesh> EquipmentStaticMesh;
	
};
