// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DDPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API ADDPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	ADDPlayerState();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Narrative Inventory")
	TObjectPtr<class UNarrativeInventoryComponent> Inventory;

	UFUNCTION(BlueprintCallable,Category = "Narrative Inventory")
	UNarrativeInventoryComponent* GetInventory() const { return Inventory; }

	
};
