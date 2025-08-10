// Fill out your copyright notice in the Description page of Project Settings.


#include "Niagara/DDFireActor.h"
#include "Niagara/DDHeterogeneousSmokeComponent.h"
#include "Character/DDCharacterPlayer.h"

// Sets default values
ADDFireActor::ADDFireActor()
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    // NiagaraComponent 생성·부착, 자동 재생 끔
    FireComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireComponent"));
    FireComponent->SetupAttachment(RootComponent);
    FireComponent->bAutoActivate = false;

    // (선택) 기본 에셋 경로 지정
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Finder(TEXT("/Game/Vefects/Free_Fire/Shared/Particles/NS_Fire_Small_Smoke.NS_Fire_Small_Smoke"));
    if (Finder.Succeeded())
    {
        FireSystem = Finder.Object;

        FireComponent->SetAsset(FireSystem);
    }

    StartScale = FVector(1.0f, 1.0f, 0.02f);
    EndScale = FVector(1.0f, 1.0f, 1.0f);
    ScaleDuration = 50.0f;

    FireComponent->SetWorldScale3D(StartScale);


    if (FireSystem)
    {
        ActivateFire();
    }

}

// Called when the game starts or when spawned
void ADDFireActor::BeginPlay()
{
	Super::BeginPlay();

    // BeginPlay 시 에셋을 컴포넌트에 설정

}

void ADDFireActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bScaling && FireComponent && FireComponent->IsActive())
    {
        ElapsedScaleTime += DeltaTime;
        float Alpha = FMath::Clamp(ElapsedScaleTime / ScaleDuration, 0.f, 5.f);

        // x, y는 고정, z만 Lerp
        FVector NewScale = StartScale;
        NewScale.Z = FMath::Lerp(StartScale.Z, EndScale.Z, Alpha);

        FireComponent->SetWorldScale3D(NewScale);

        if (Alpha >= 1.f)
        {
            bScaling = false;
        }
    }

}

void ADDFireActor::ActivateFire()
{
    if (FireComponent && !FireComponent->IsActive())
    {
        ElapsedScaleTime = 0.f;
        bScaling = true;
        FireComponent->SetWorldScale3D(StartScale);

        FireComponent->SetAsset(FireSystem);
        FireComponent->Activate(true);
    }
}

void ADDFireActor::DeactiveFire()
{
    if (FireComponent && FireComponent->IsActive())
    {
        FireComponent->Deactivate();
        bScaling = false;




    }
}
