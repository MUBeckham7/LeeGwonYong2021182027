// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DDUserWidget.h"
#include "DDStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API UDDStateWidget : public UDDUserWidget
{
	GENERATED_BODY()
	

public:

	UDDStateWidget(const FObjectInitializer& ObjectInitializer);

public:
	FORCEINLINE void SetMaxHunger(float NewMaxHunger) { MaxHunger = NewMaxHunger; }
	void UpdateHunger(float NewCurrentHunger);
	FORCEINLINE void SetMaxThirst(float NewMaxThirst) { MaxThirst = NewMaxThirst; }
	void UpdateThirst(float NewCurrentThirst);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class UImage> HungerGauge;

	UPROPERTY()
	TObjectPtr<class UImage> ThirstGauge;

	//UPROPERTY(meta = (BindWidget))
	//class UImage* Img_Circular_1;



	//UPROPERTY(meta = (BindWidget))
	//class UImage* Img_Circular;

	UPROPERTY()
	UMaterialInstanceDynamic* HungerGaugeMID;

	UPROPERTY()
	UMaterialInstanceDynamic* ThirstGaugeMID;

	UPROPERTY()
	float MaxHunger;

	UPROPERTY()
	float MaxThirst;


};
