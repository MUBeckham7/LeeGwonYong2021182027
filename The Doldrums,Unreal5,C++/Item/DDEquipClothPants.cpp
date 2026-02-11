// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DDEquipClothPants.h"
#include "Collision/DDCollision.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Interface/DDCharacterItemInterface.h"

// Sets default values
ADDEquipClothPants::ADDEquipClothPants()
{
	TriggerPants = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	Pants = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TShirt"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = TriggerPants;
	Pants->SetupAttachment(TriggerPants);

	TriggerPants->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerPants->SetBoxExtent(FVector(70.0f, 105.0f, 750.0f));
	TriggerPants->SetRelativeLocation(FVector(521.0f, -16.0f, 0.0f));
	TriggerPants->OnComponentBeginOverlap.AddDynamic(this, &ADDEquipClothPants::OnOverlapBegin);
	TriggerPants->OnComponentEndOverlap.AddDynamic(this, &ADDEquipClothPants::OnOverlapEnd);
	///Script/Engine.SkeletalMesh'/Game/PostApoClothing/Meshes/MaleAverageNormal/SKM_MAN_Pant.SKM_MAN_Pant'

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>PantsMeshRef(TEXT("Script/Engine.SkeletalMesh'/Game/PostApoClothing/Meshes/MaleAverageNormal/SKM_MAN_Pant.SKM_MAN_Pant'"));
	if (PantsMeshRef.Object) {
		Pants->SetSkeletalMesh(PantsMeshRef.Object);
	}

}

// Called when the game starts or when spawned
void ADDEquipClothPants::BeginPlay()
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

void ADDEquipClothPants::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ItemWidget->SetVisibility(ESlateVisibility::Visible);

	PlayerActor = OtherActor;


}

void ADDEquipClothPants::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ADDEquipClothPants::OnInteract()
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
			Pants->SetHiddenInGame(true);
			SetActorEnableCollision(false);

			IDDCharacterItemInterface* OverlappingPawn = Cast<IDDCharacterItemInterface>(PlayerActor);
			if (OverlappingPawn)
			{
				OverlappingPawn->TakeItem(Item);
			}

		}
	}
}

