// Fill out your copyright notice in the Description page of Project Settings.


#include "Niagara/DDHeterogeneousSmokeComponent.h"

// Sets default values for this component's properties
UDDHeterogeneousSmokeComponent::UDDHeterogeneousSmokeComponent()
{

	PrimaryComponentTick.bCanEverTick = true;


    static ConstructorHelpers::FObjectFinder<UMaterialInstance> Finder(
        TEXT("/Game/MistAndSteamPack/Materials/Instance/GroundSteam/MI_GroundSteamLoopA_LOD2.MI_GroundSteamLoopA_LOD2")
    );
    if (Finder.Succeeded())
    {
        BaseMaterial = Finder.Object;

    }

}

void UDDHeterogeneousSmokeComponent::OnRegister()
{
    Super::OnRegister();

    if (!VolumeComp && GetOwner())
    {
        VolumeComp = NewObject<UHeterogeneousVolumeComponent>(
            GetOwner(),
            UHeterogeneousVolumeComponent::StaticClass(),
            TEXT("HeteroVol"),
            RF_Transactional
        );
        VolumeComp->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
        VolumeComp->RegisterComponent();

        VolumeComp->SetStartFrame(0.f);
        VolumeComp->SetEndFrame(174.f);
        VolumeComp->SetFrameRate(24.f);
        VolumeComp->SetLooping(true);
        VolumeComp->SetPlaying(false);

        VolumeComp->SetAbsolute(false,true,false);
    }

    // DynamicMaterial 세팅
    if (BaseMaterial && VolumeComp)
    {
        UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(BaseMaterial, this);
        VolumeComp->SetMaterial(0, DynMat);
    }


}


// Called every frame
void UDDHeterogeneousSmokeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!VolumeComp || !VolumeComp->bPlaying)
    {
        return;
    }

    float NewFrame = VolumeComp->Frame + DeltaTime * VolumeComp->FrameRate;
    if (NewFrame > VolumeComp->EndFrame)
    {
        NewFrame = VolumeComp->bLooping ? VolumeComp->StartFrame : VolumeComp->EndFrame;
        if (!VolumeComp->bLooping)
            VolumeComp->SetPlaying(false);
    }

    VolumeComp->SetFrame(NewFrame);

    if (bScaling)
    {
        CurrentScaleTime += DeltaTime;
        float Alpha = FMath::Clamp(CurrentScaleTime / ScaleDuration, 0.f, 1.f);
        FVector NewScale = FMath::Lerp(StartScale, EndScale, Alpha);
        VolumeComp->SetRelativeScale3D(NewScale);

        if (Alpha >= 1.f)
        {
            bScaling = false;
        }
    }
}

void UDDHeterogeneousSmokeComponent::PlaySmoke()
{
    if (!VolumeComp) return;

    // 재생과 동시에 스케일 초기화
    VolumeComp->SetPlaying(true);
    VolumeComp->SetRelativeScale3D(StartScale);

    CurrentScaleTime = 0.f;
    bScaling = true;
}

void UDDHeterogeneousSmokeComponent::StopSmoke()
{
    if (VolumeComp)
    {
        VolumeComp->SetPlaying(false);
        bScaling = false;

        VolumeComp->DestroyComponent(false);

        VolumeComp = nullptr;
    }
        PrimaryComponentTick.bCanEverTick = false;

}

