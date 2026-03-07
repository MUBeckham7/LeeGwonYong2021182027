// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/HeterogeneousVolumeComponent.h"
#include "DDHeterogeneousSmokeComponent.generated.h"


UCLASS( ClassGroup=(Custom), Blueprintable ,meta=(BlueprintSpawnableComponent) )
class THEDOLDRUMS_API UDDHeterogeneousSmokeComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDDHeterogeneousSmokeComponent();

protected:
	// Called when the game starts
	virtual void OnRegister() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Smoke")
	void PlaySmoke();

	UFUNCTION(BlueprintCallable, Category = "Smoke")
	void StopSmoke();

private:
	// 내부 볼륨 컴포넌트
	UPROPERTY()
	UHeterogeneousVolumeComponent* VolumeComp;

	// 머티리얼 레퍼런스
	UPROPERTY(EditAnywhere, Category = "Smoke")
	TObjectPtr<class UMaterialInstance> BaseMaterial;

	UPROPERTY(EditAnywhere, Category = "Smoke|Scale")
	FVector StartScale = FVector(0.2f);

	UPROPERTY(EditAnywhere, Category = "Smoke|Scale")
	FVector EndScale = FVector(1.0f);

	UPROPERTY(EditAnywhere, Category = "Smoke|Scale", meta = (ClampMin = "0.01"))
	float ScaleDuration = 1.0f;  // 초 단위

	float     CurrentScaleTime = 0.0f;
	bool      bScaling = false;
		
};
