// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DDTimeWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"



void UDDTimeWidget::CaculateDayTime(float AccumulatedRotation)
{


	uint32 Day = FMath::FloorToInt(AccumulatedRotation / 360.0f) + 1;

	float Remainder = FMath::Fmod(AccumulatedRotation , 360.0f);

	float TotalHours = (Remainder / 360.0f) * 24.0f;

	uint32 Hour = FMath::FloorToInt(TotalHours);

	float FractionalHour = TotalHours - Hour;
	uint32 Minute = FMath::FloorToInt(FractionalHour * 60.0f);

	FText DayText = FText::Format(NSLOCTEXT("TimeWidget", "DayFormat", "Day:{0}"), FText::AsNumber(Day));
	FText TimeText = FText::Format(NSLOCTEXT("TimeWidget", "TimeFormat", "{0} : {1}"), FText::AsNumber(Hour), FText::AsNumber(Minute));

	if (DayTextBlock)
	{
		DayTextBlock->SetText(DayText);
	}
	if (TimeTextBlock)
	{
		TimeTextBlock->SetText(TimeText);
	}
}

