// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DDCharacterItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDDCharacterItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THEDOLDRUMS_API IDDCharacterItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void TakeItem(class UDDItemDataAsset* InItemData) = 0 ;
};
