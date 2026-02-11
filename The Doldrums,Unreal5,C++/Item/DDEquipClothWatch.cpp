// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DDEquipClothWatch.h"
#include "Collision/DDCollision.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Interface/DDCharacterItemInterface.h"


// Sets default values
ADDEquipClothWatch::ADDEquipClothWatch()
{

	TriggerWatch = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	Watch = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Watch"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = TriggerWatch;
	Watch->SetupAttachment(TriggerWatch);

	TriggerWatch->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerWatch->SetBoxExtent(FVector(70.0f, 105.0f, 750.0f));
	TriggerWatch->SetRelativeLocation(FVector(521.0f, -16.0f, 0.0f));
	TriggerWatch->OnComponentBeginOverlap.AddDynamic(this, &ADDEquipClothWatch::OnOverlapBegin);
	TriggerWatch->OnComponentEndOverlap.AddDynamic(this, &ADDEquipClothWatch::OnOverlapEnd);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>WatchMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/PostApoClothing/Meshes/MaleAverageNormal/SKM_MAN_Watch.SKM_MAN_Watch'"));
	if (WatchMeshRef.Object) {
		Watch->SetSkeletalMesh(WatchMeshRef.Object);
	}
}

// Called when the game starts or when spawned
void ADDEquipClothWatch::BeginPlay()
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

void ADDEquipClothWatch::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ItemWidget->SetVisibility(ESlateVisibility::Visible);

	PlayerActor = OtherActor;

}

void ADDEquipClothWatch::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);

}

void ADDEquipClothWatch::OnInteract()
{
	if (nullptr == Item)
	{
		Destroy();
		return;
	}

	if (ItemWidget->IsVisible())
	{
		if (PlayerActor)
		{
			Watch->SetHiddenInGame(true);
			SetActorEnableCollision(false);

			IDDCharacterItemInterface* OverlappingPawn = Cast<IDDCharacterItemInterface>(PlayerActor);
			if (OverlappingPawn)
			{
				OverlappingPawn->TakeItem(Item);
			}

		}
	}

}


