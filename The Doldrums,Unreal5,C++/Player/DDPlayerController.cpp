// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DDPlayerController.h"
#include "Components/WidgetComponent.h"


ADDPlayerController::ADDPlayerController()
{

	BagMeshPart1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EquipmentBagBody"));


	BagMeshPart2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EquipmentBagTie"));

}

void ADDPlayerController::BeginPlay()
{

	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);



}
