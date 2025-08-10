// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "DDFireActor.generated.h"

UCLASS()
class THEDOLDRUMS_API ADDFireActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDFireActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable,Category = "Fire")
	void ActivateFire();

	UFUNCTION(BlueprintCallable,Category = "Fire")
	void DeactiveFire();

private:
	UPROPERTY(EditAnywhere,Category = "Fire")
	UNiagaraSystem* FireSystem;

	UPROPERTY(VisibleAnywhere,Category = "Fire")
	UNiagaraComponent* FireComponent;

	UPROPERTY(EditAnywhere, Category = "Fire|Scale")
	FVector StartScale;

	UPROPERTY(EditAnywhere, Category = "Fire|Scale")
	FVector EndScale;

	UPROPERTY(EditAnywhere, Category = "Fire|Scale", meta = (ClampMin = "0.01"))
	float ScaleDuration;  // √  ¥‹¿ß

	float  ElapsedScaleTime = 0.0f;
	bool   bScaling = false;

};
