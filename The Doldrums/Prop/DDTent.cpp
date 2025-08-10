// Fill out your copyright notice in the Description page of Project Settings.

#include "Prop/DDTent.h"
#include "Components/BoxComponent.h"
#include "Collision/DDCollision.h"
#include "Engine/EngineTypes.h"
#include "Interface/DDItemInteractionInterface.h"
#include "Components/WidgetComponent.h"
#include "DayNight/DDdaynightskysun.h"
#include <Kismet/GameplayStatics.h>

ADDTent::ADDTent()
{
	TriggerTent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	Tent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tent"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = TriggerTent;
	Tent->SetupAttachment(TriggerTent);

	TriggerTent->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerTent->SetBoxExtent(FVector(70.0f, 105.0f, 750.0f));
	TriggerTent->SetRelativeLocation(FVector(521.0f, -16.0f, 0.0f));
	TriggerTent->OnComponentBeginOverlap.AddDynamic(this, &ADDTent::OnOverlapBegin);
	TriggerTent->OnComponentEndOverlap.AddDynamic(this, &ADDTent::OnOverlapEnd);


	static ConstructorHelpers::FObjectFinder<UStaticMesh>TentMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Prop/Tent/scene.scene'"));
	if (TentMeshRef.Object) {
		Tent->SetStaticMesh(TentMeshRef.Object);
	}

}

void ADDTent::BeginPlay()
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

void ADDTent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ItemWidget->SetVisibility(ESlateVisibility::Visible);

	PlayerActor = OtherActor;

}

void ADDTent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);
	PlayerActor = nullptr;
}

void ADDTent::OnInteract()
{
	if (ItemWidget->IsVisible())
	{
		if (PlayerActor)
		{
			UE_LOG(LogTemp, Log, TEXT("PlayActor is Not Null"));
			TArray<AActor*> ActorsToFind;
			if (UWorld* World = GetWorld())
			{
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADDdaynightskysun::StaticClass(), ActorsToFind);

				UE_LOG(LogTemp, Log, TEXT("World is Not Null"));
			}

			for (AActor* DayNight : ActorsToFind)
			{
				ADDdaynightskysun* DNSS = Cast<ADDdaynightskysun>(DayNight);
				if (DNSS)
				{			
					DNSS->NextDay();
				}
			}


		}
	}

}
