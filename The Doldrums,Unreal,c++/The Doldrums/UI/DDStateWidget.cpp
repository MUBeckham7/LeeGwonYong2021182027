// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DDStateWidget.h"
#include "Components/Image.h"
#include "Interface/DDCharacterWidgetInterface.h"

UDDStateWidget::UDDStateWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHunger = -1.0f;
	MaxThirst = -1.0f;
}

void UDDStateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//OwningActor 

	//HungerImg = Cast<UImage>(GetWidgetFromName(TEXT("HungerImage")));
	//ensure(HungerImg);


	HungerGauge = Cast<UImage>(GetWidgetFromName(TEXT("Img_Circular_1")));
	ensure(HungerGauge);

	ThirstGauge = Cast<UImage>(GetWidgetFromName(TEXT("Img_Circular")));
	ensure(ThirstGauge);


	if (HungerGauge)
	{
		HungerGaugeMID = HungerGauge->GetDynamicMaterial();

		
	}

	if (ThirstGauge)
	{
		ThirstGaugeMID = ThirstGauge->GetDynamicMaterial();

	}

	IDDCharacterWidgetInterface* CharacterWidget = Cast<IDDCharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupHungerCharacterWidget(this);
		CharacterWidget->SetupThirstCharacterWidget(this);
	}

}


void UDDStateWidget::UpdateHunger(float NewCurrentHunger)
{

	if (HungerGaugeMID && MaxHunger>0.0f)
	{

		float Percent = NewCurrentHunger / MaxHunger;
		HungerGaugeMID->SetScalarParameterValue(TEXT("Gauge"), Percent);
	}

}

void UDDStateWidget::UpdateThirst(float NewCurrentThirst)
{
	if (ThirstGaugeMID)
	{
		float Percent = NewCurrentThirst / MaxThirst;
		ThirstGaugeMID->SetScalarParameterValue(TEXT("Gauge"), Percent);
	}

}