// Fill out your copyright notice in the Description page of Project Settings.

#include "DayNight/DDdaynightskysun.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/SkyLightComponent.h"
#include "UI/DDTimeWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/VolumetricCloudComponent.h"
#include "Components/DirectionalLightComponent.h"
#include <Engine/ExponentialHeightFog.h>
#include <Engine/SkyLight.h>

// Sets default values
ADDdaynightskysun::ADDdaynightskysun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurnRate = 15.0f;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Sun = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("SunDirectionalLight"));
	Moon = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("MoonDirectionalLight"));
	SkyAtmosphere = CreateDefaultSubobject<USkyAtmosphereComponent>(TEXT("SkyAtmoSphere"));
	SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
	HeightFog = CreateDefaultSubobject<UExponentialHeightFogComponent>(TEXT("ExponentialHeightFog"));
	VolumetricCloud = CreateDefaultSubobject<UVolumetricCloudComponent>(TEXT("VolumetricFog"));
	SkySphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_SkySphere"));

	RootComponent = Root;
	Sun->SetupAttachment(RootComponent);
	Moon->SetupAttachment(RootComponent);
	SkyAtmosphere->SetupAttachment(RootComponent);
	SkyLight->SetupAttachment(RootComponent);
	HeightFog->SetupAttachment(RootComponent);
	VolumetricCloud->SetupAttachment(RootComponent);
	SkySphere->SetupAttachment(Moon);

	///DirectionalLight -- Sun		2		3		1
	//Sun->SetRelativeRotator(-35,-180,0) -55,180,0
	 


	//DirectionalLight -- Moon
	//Moon->SetRelativeRotator(-35,360,0) -55,0,0
	Moon->Intensity = 0.025f;
	Moon->LightSourceAngle = 0.0f;
	Moon->bUseTemperature = true;
	Moon->Temperature = 12000.0f;
	Moon->bAtmosphereSunLight = false;
	Moon->ForwardShadingPriority = 1;
	Moon->SetLightingChannels(false, true, false);
	Moon->bAtmosphereSunLight = true;


	/////SkyLight
	SkyLight->SetMobility(EComponentMobility::Movable);
	SkyLight->bRealTimeCapture = true;
	SkyLight->Intensity = 0.5f;
	SkyLight->IndirectLightingIntensity = 0.1f;

	//SkySphere
	//SkySphere Rotation -39,168,122   1,42,49


	static ConstructorHelpers::FObjectFinder<UStaticMesh>SmSkySphere(TEXT("/Script/Engine.StaticMesh'/Engine/EngineSky/SM_SkySphere.SM_SkySphere'"));
	if (SmSkySphere.Object) {
		SkySphere->SetStaticMesh(SmSkySphere.Object);
	}

	SkySphere->SetRelativeScale3D(FVector3d(150000.0f, 150000.0f, 150000.0f));

}

// Called when the game starts or when spawned
void ADDdaynightskysun::BeginPlay()
{
	Super::BeginPlay();

	if (DayTimeWidgetClass)
	{
		DayTimeWidgetInstance = CreateWidget<UDDTimeWidget>(GetWorld(), DayTimeWidgetClass);


		if (DayTimeWidgetClass)
		{
			DayTimeWidgetInstance->AddToViewport();
		}

	}

	InitSunRot = Sun->GetRelativeRotation();
	InitMoonRot = Moon->GetRelativeRotation();
	AccumulatedRotation = 90.0f;

}

void ADDdaynightskysun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Sun)
	{
		Sun->AddLocalRotation(FRotator(0,(DeltaTime * TurnRate), 0));

		AccumulatedRotation += DeltaTime * TurnRate;

		if (DayTimeWidgetInstance)
		{
			DayTimeWidgetInstance->CaculateDayTime(AccumulatedRotation);
		}

	}
	if (Moon)
	{
		Moon->AddLocalRotation(FRotator((DeltaTime * TurnRate),0 , 0));
	}

	if (Sun->GetRelativeRotation().Pitch > 0)
	{
		Sun->SetVisibility(false);
		Moon->SetVisibility(true);
	}
	else
	{
		Sun->SetVisibility(true);
		Moon->SetVisibility(true);
	}


}

void ADDdaynightskysun::NextDay() const
{
	if (Sun->GetRelativeRotation().Pitch > 0)
	{
		Sun->SetRelativeRotation(InitSunRot);
		Moon->SetRelativeRotation(InitMoonRot);;

	}
	else
	{
		Sun->SetRelativeRotation(InitSunRot);
		Moon->SetRelativeRotation(InitMoonRot);;
	}


}


