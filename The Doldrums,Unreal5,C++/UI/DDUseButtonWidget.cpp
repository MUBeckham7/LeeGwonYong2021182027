// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DDUseButtonWidget.h"
#include "Components/Button.h"
#include "NarrativeItem.h"

void UDDUseButtonWidget::NativeConstruct()
{

	if (Button_Use)
	{
		Button_Use->OnClicked.AddDynamic(this, &UDDUseButtonWidget::OnUseClicked);
	}
	if (Button_Drop)
	{
		Button_Drop->OnClicked.AddDynamic(this, &UDDUseButtonWidget::OnDropClicked);
	}

}

void UDDUseButtonWidget::OnUseClicked()
{
	if (!ItemData) return;

	UE_LOG(LogTemp, Log, TEXT("FUCKCKCKCKCKCK"));

}

void UDDUseButtonWidget::OnDropClicked()
{
	if (!ItemData) return;


}
