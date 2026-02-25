// Fill out your copyright notice in the Description page of Project Settings.


#include "Niagara/DDFireActor.h"
#include "Collision/DDCollision.h"
#include "Niagara/DDHeterogeneousSmokeComponent.h"
#include "Character/DDCharacterPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ADDFireActor::ADDFireActor()
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    TriggerFire = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerFire"));
    Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));
    // NiagaraComponent 생성·부착, 자동 재생 끔
    FireComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireComponent"));

    TriggerFire->SetupAttachment(RootComponent);

    TriggerFire->SetCollisionProfileName(CPROFILE_DDTRIGGER);
    TriggerFire->SetBoxExtent(FVector(80.f, 80.f, 80.f));
    TriggerFire->OnComponentBeginOverlap.AddDynamic(this, &ADDFireActor::OnOverlapBegin);
    TriggerFire->OnComponentEndOverlap.AddDynamic(this, &ADDFireActor::OnOverlapEnd);

    FireComponent->SetupAttachment(TriggerFire);
    FireComponent->bAutoActivate = false;

    // (선택) 기본 에셋 경로 지정
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Finder(TEXT("/Game/Vefects/Free_Fire/Shared/Particles/NS_Fire_Small_Smoke.NS_Fire_Small_Smoke"));
    if (Finder.Succeeded())
    {
        FireSystem = Finder.Object;

        FireComponent->SetAsset(FireSystem);
    }

    static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
    if (InputE.Succeeded())
    {
        InteractionItemWidgetClass = InputE.Class;
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

    if (InteractionItemWidgetClass)
    {
        ItemWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionItemWidgetClass);
        if (ItemWidget)
        {
            ItemWidget->AddToViewport();
            ItemWidget->SetVisibility(ESlateVisibility::Hidden);
        }

    }

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

void ADDFireActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
    ItemWidget->SetVisibility(ESlateVisibility::Visible);

    PlayerActor = OtherActor;
}

void ADDFireActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ItemWidget->SetVisibility(ESlateVisibility::Hidden);

}
