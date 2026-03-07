// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DDEquipClothTShirt.h"
#include "Collision/DDCollision.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Interface/DDCharacterItemInterface.h"


// Sets default values
ADDEquipClothTShirt::ADDEquipClothTShirt()
{
	TriggerTShirt = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	TShirt = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TShirt"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = TriggerTShirt;
	TShirt->SetupAttachment(TriggerTShirt);

	TriggerTShirt->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerTShirt->SetBoxExtent(FVector(70.0f, 105.0f, 750.0f));
	TriggerTShirt->SetRelativeLocation(FVector(521.0f, -16.0f, 0.0f));
	TriggerTShirt->OnComponentBeginOverlap.AddDynamic(this, &ADDEquipClothTShirt::OnOverlapBegin);
	TriggerTShirt->OnComponentEndOverlap.AddDynamic(this, &ADDEquipClothTShirt::OnOverlapEnd);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>TShirtMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/PostApoClothing/Meshes/MaleAverageNormal/SKM_MAN_TShirt.SKM_MAN_TShirt'"));
	if (TShirtMeshRef.Object) {
		TShirt->SetSkeletalMesh(TShirtMeshRef.Object);
	}

}

// Called when the game starts or when spawned
void ADDEquipClothTShirt::BeginPlay()
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

void ADDEquipClothTShirt::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ItemWidget->SetVisibility(ESlateVisibility::Visible);

	PlayerActor = OtherActor;

}

void ADDEquipClothTShirt::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);

}

void ADDEquipClothTShirt::OnInteract()
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
			TShirt->SetHiddenInGame(true);
			SetActorEnableCollision(false);

			IDDCharacterItemInterface* OverlappingPawn = Cast<IDDCharacterItemInterface>(PlayerActor);
			if (OverlappingPawn)
			{
				OverlappingPawn->TakeItem(Item);
			}

		}
	}

}


