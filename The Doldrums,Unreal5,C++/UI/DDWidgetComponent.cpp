// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DDWidgetComponent.h"
#include "DDUserWidget.h"

void UDDWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UDDUserWidget* DDUserWidget = Cast<UDDUserWidget>(GetWidget());
	if (DDUserWidget)
	{
		DDUserWidget->SetOwningActor(GetOwner());
	}
}
