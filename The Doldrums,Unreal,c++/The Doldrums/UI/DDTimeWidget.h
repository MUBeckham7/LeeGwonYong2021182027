// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DDTimeWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API UDDTimeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void CaculateDayTime(float AccumulatedRotation);

protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DayTextBlock;


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TimeTextBlock;
};
