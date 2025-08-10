// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DirectionalLight.h"
#include "Misc/OutputDeviceNull.h"
#include "DDdaynightskysun.generated.h"

class UDDTimeWidget;

UCLASS()
class THEDOLDRUMS_API ADDdaynightskysun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDdaynightskysun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USceneComponent> Root;


	UPROPERTY(EditAnywhere,Category = "Sky")
	TObjectPtr<class UDirectionalLightComponent> Sun;

	UPROPERTY(EditAnywhere, Category = "Sky")
	TObjectPtr<class UDirectionalLightComponent> Moon;

	UPROPERTY(EditAnywhere,Category = "Sky")
	TObjectPtr<class USkyAtmosphereComponent> SkyAtmosphere;

	UPROPERTY(EditAnywhere, Category = "Sky")
	TObjectPtr <class USkyLightComponent> SkyLight;

	UPROPERTY(EditAnywhere, Category = "Sky")
	TObjectPtr <class UExponentialHeightFogComponent>HeightFog;

	UPROPERTY(EditAnywhere, Category = "Sky")
	TObjectPtr <class UVolumetricCloudComponent>VolumetricCloud;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> SkySphere;


	UPROPERTY(EditAnywhere, Category = "Sky")
	float TurnRate;

	float AccumulatedRotation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "UI")
	TSubclassOf<UDDTimeWidget> DayTimeWidgetClass;

	UPROPERTY()
	UDDTimeWidget* DayTimeWidgetInstance;

	UFUNCTION()
	void NextDay() const;

	FRotator3d InitSunRot;
	FRotator3d InitMoonRot;

};
