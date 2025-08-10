// Fill out your copyright notice in the Description page of Project Settings.


#include "State/DDPlayerState.h"
#include "InventoryComponent.h"

ADDPlayerState::ADDPlayerState()
{


	Inventory = CreateDefaultSubobject<UNarrativeInventoryComponent>(TEXT("Inventory"));

}
