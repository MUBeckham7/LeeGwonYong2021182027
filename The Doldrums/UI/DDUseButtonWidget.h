// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DDUseButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API UDDUseButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Use;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Drop;

	UPROPERTY(BlueprintReadOnly,Category = "Item")
	TSubclassOf<class UNarrativeItem>ItemData;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnUseClicked();

	UFUNCTION()
	void OnDropClicked();


	
};
