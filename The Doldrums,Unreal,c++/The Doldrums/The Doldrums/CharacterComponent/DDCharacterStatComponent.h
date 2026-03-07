// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DDCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHungerZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHungerChangedDelegate,float);
DECLARE_MULTICAST_DELEGATE(FOnThirstZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnThirstChangedDelegate, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEDOLDRUMS_API UDDCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDDCharacterStatComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FOnHungerZeroDelegate OnHungerZero;
	FOnHungerChangedDelegate OnHungerChanged;
	FOnThirstZeroDelegate OnThirstZero;
	FOnThirstChangedDelegate OnThirstChanged;

	FORCEINLINE float GetMaxHunger() { return MaxHunger;}
	FORCEINLINE float GetCurrentHunger() { return CurrentHunger; }
	FORCEINLINE float GetMaxThirst() { return MaxThirst; }
	FORCEINLINE float GetCurrentThirst() { return CurrentThirst; }

	UFUNCTION(BlueprintCallable)
	float DecreaseHungerStat(float InDamage);
	UFUNCTION(BlueprintCallable)
	float DecreaseThirstStat(float InDamage);
	UFUNCTION(BlueprintCallable)
	float IncreaseHungerStat(float InDamage);
	UFUNCTION(BlueprintCallable)
	float IncreaseThirstStat(float InDamage);


protected:
	void SetHunger(float NewHungerStat);
	void SetThirst(float NewThirstStat);

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float MaxHunger;

	UPROPERTY(Transient, VisibleInstanceOnly, ReplicatedUsing = OnRep_CurrentHunger, Category = Stat)
	float CurrentHunger;

	UFUNCTION()
	void OnRep_CurrentHunger();

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float MaxThirst;

	UPROPERTY(Transient, VisibleInstanceOnly, ReplicatedUsing = OnRep_CurrentHunger, Category = Stat)
	float CurrentThirst;

	UFUNCTION()
	void OnRep_CurrentThirst();
		
};
