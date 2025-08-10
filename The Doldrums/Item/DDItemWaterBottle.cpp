// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DDItemWaterBottle.h"
#include "Components/BoxComponent.h"
#include "Collision/DDCollision.h"
#include "Components/WidgetComponent.h"
#include "Interface/DDCharacterItemInterface.h"
#include "State/DDPlayerState.h"
#include "NarrativeItem.h"


// Sets default values
ADDItemWaterBottle::ADDItemWaterBottle()
{
	TriggerWaterBottle = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	WaterBottle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Branch"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = TriggerWaterBottle;
	WaterBottle->SetupAttachment(TriggerWaterBottle);

	WaterBottle->SetWorldRotation(FRotator(0.0f,0.0f,90.0f));

	TriggerWaterBottle->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerWaterBottle->SetBoxExtent(FVector(70.0f, 105.0f, 750.0f));
	TriggerWaterBottle->OnComponentBeginOverlap.AddDynamic(this, &ADDItemWaterBottle::OnOverlapBegin);
	TriggerWaterBottle->OnComponentEndOverlap.AddDynamic(this, &ADDItemWaterBottle::OnOverlapEnd);


	static ConstructorHelpers::FObjectFinder<UStaticMesh>WaterBottleMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Prop/Bottle/NewFolder1/WaterBottle.WaterBottle'"));
	if (WaterBottleMeshRef.Object) {
		WaterBottle->SetStaticMesh(WaterBottleMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UDDItemDataAsset>WaterBottleDataAssetRef(TEXT("/Script/TheDoldrums.DDEquipmentItemData'/Game/Item/Equipment/DDIW_WaterBottle.DDIW_WaterBottle'"));
	if (WaterBottleDataAssetRef.Succeeded())
	{
		Item = WaterBottleDataAssetRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UNarrativeItem>InvWaterBottleDataAssetRef(TEXT("/Game/Item/Equipment/BPI_WaterBottle.BPI_WaterBottle_C"));
	if (InvWaterBottleDataAssetRef.Succeeded())
	{
		ItemDDWaterBottleClass = InvWaterBottleDataAssetRef.Class;
	}

}

// Called when the game starts or when spawned
void ADDItemWaterBottle::BeginPlay()
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

void ADDItemWaterBottle::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ItemWidget->SetVisibility(ESlateVisibility::Visible);

	PlayerActor = OtherActor;
}

void ADDItemWaterBottle::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ADDItemWaterBottle::OnInteract()
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
			WaterBottle->SetHiddenInGame(true);
			SetActorEnableCollision(false);

			IDDCharacterItemInterface* OverlappingPawn = Cast<IDDCharacterItemInterface>(PlayerActor);
			if (OverlappingPawn)
			{
				OverlappingPawn->TakeItem(Item);
				Destroy();
			}

			APawn* Pawn = Cast<APawn>(PlayerActor);
			if (Pawn)
			{
				ADDPlayerState* MyPs = Pawn->GetPlayerState<ADDPlayerState>();
				if (MyPs && MyPs->Inventory)
				{
					MyPs->Inventory->TryAddItemFromClass(ItemDDWaterBottleClass, 1);
				}
			}

		}
	}

}

