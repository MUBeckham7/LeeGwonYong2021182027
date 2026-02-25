// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/DDCharacterStatComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UDDCharacterStatComponent::UDDCharacterStatComponent()
{
	MaxHunger = 100.0f;
	CurrentHunger = MaxHunger;
	MaxThirst = 100.0f;
	CurrentThirst = MaxThirst;
}

void UDDCharacterStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// CurrentHunger와 CurrentThirst를 모든 클라이언트에게 복제
	DOREPLIFETIME(UDDCharacterStatComponent, CurrentHunger);
	DOREPLIFETIME(UDDCharacterStatComponent, CurrentThirst);

}


// Called when the game starts
void UDDCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	

	SetHunger(MaxHunger);
	SetThirst(MaxThirst);

}

float UDDCharacterStatComponent::DecreaseHungerStat(float InDamage)
{
	const float PrevHungerStat = CurrentHunger;
	const float ActualDecrease = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHunger(PrevHungerStat - ActualDecrease);
	if (CurrentHunger <= KINDA_SMALL_NUMBER)
	{
		OnHungerZero.Broadcast();
	}


	return ActualDecrease;
}

float UDDCharacterStatComponent::DecreaseThirstStat(float InDamage)
{
	const float PrevThirstStat = CurrentThirst;
	const float ActualDecrease = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetThirst(PrevThirstStat - ActualDecrease);
	if (CurrentThirst <= KINDA_SMALL_NUMBER)
	{
		OnThirstZero.Broadcast();
	}


	return ActualDecrease;
}

float UDDCharacterStatComponent::IncreaseHungerStat(float InDamage)
{
	const float PrevHungerStat = CurrentHunger;
	const float ActualIncrease = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHunger(PrevHungerStat + ActualIncrease);


	return ActualIncrease;

}

float UDDCharacterStatComponent::IncreaseThirstStat(float InDamage)
{
	const float PrevThirstStat = CurrentThirst;
	const float ActualIncrease = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetThirst(PrevThirstStat + ActualIncrease);


	return ActualIncrease;

}


void UDDCharacterStatComponent::SetHunger(float NewHungerStat)
{
	CurrentHunger = FMath::Clamp<float>(NewHungerStat, 0.0f, MaxHunger);
	OnHungerChanged.Broadcast(CurrentHunger);
}

void UDDCharacterStatComponent::SetThirst(float NewThirstStat)
{
	CurrentThirst = FMath::Clamp<float>(NewThirstStat, 0.0f, MaxHunger);
	OnThirstChanged.Broadcast(CurrentThirst);
}

void UDDCharacterStatComponent::OnRep_CurrentHunger()
{
	OnHungerChanged.Broadcast(CurrentHunger);
}

void UDDCharacterStatComponent::OnRep_CurrentThirst()
{
	OnThirstChanged.Broadcast(CurrentThirst);
}



