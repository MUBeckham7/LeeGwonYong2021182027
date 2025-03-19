// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DDPlayerController.h"

void ADDPlayerController::BeginPlay()
{

	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);


}
