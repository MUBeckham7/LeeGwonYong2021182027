// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WMAWidgetAttacked2.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API UWMAWidgetAttacked2 : public UUserWidget
{
	GENERATED_BODY()

public:
	UWMAWidgetAttacked2(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

protected:

	UPROPERTY()
	TObjectPtr<class UImage> SecondAttackedWidget;

private:
	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeIn;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeOut;

public:

	void FadeInAnim();
	void FadeOutAnim();

};
