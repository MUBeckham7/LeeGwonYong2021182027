// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DDItemAxe.h"
#include "Collision/DDCollision.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Interface/DDCharacterItemInterface.h"
#include "State/DDPlayerState.h"
#include "NarrativeItem.h"

// Sets default values
ADDItemAxe::ADDItemAxe()
{
	TriggerAxe = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	Axe = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Axe"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = TriggerAxe;
	Axe->SetupAttachment(TriggerAxe);

	TriggerAxe->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerAxe->SetBoxExtent(FVector(70.0f, 105.0f, 750.0f));
	//->SetRelativeLocation(FVector(521.0f, -16.0f, 0.0f));
	TriggerAxe->OnComponentBeginOverlap.AddDynamic(this, &ADDItemAxe::OnOverlapBegin);
	TriggerAxe->OnComponentEndOverlap.AddDynamic(this, &ADDItemAxe::OnOverlapEnd);


	static ConstructorHelpers::FObjectFinder<UStaticMesh>AxeMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Prop/Axe/simple_axe.simple_axe'"));
	if (AxeMeshRef.Object) {
		Axe->SetStaticMesh(AxeMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UDDItemDataAsset>AxeDataAssetRef(TEXT("/Script/TheDoldrums.DDEquipmentItemData'/Game/Item/Equipment/DDIW_Axe.DDIW_Axe'"));
	if (AxeDataAssetRef.Succeeded())
	{
		Item = AxeDataAssetRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UNarrativeItem>InvAxeDataAssetRef(TEXT("/Game/Item/Equipment/BPI_Axe.BPI_Axe_C"));
	if (InvAxeDataAssetRef.Succeeded())
	{
		ItemDDAxeClass = InvAxeDataAssetRef.Class;
	}
}

// Called when the game starts or when spawned
void ADDItemAxe::BeginPlay()
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

void ADDItemAxe::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ItemWidget->SetVisibility(ESlateVisibility::Visible);

	PlayerActor = OtherActor;
}

void ADDItemAxe::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ADDItemAxe::OnInteract()
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
			Axe->SetHiddenInGame(true);
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
					MyPs->Inventory->TryAddItemFromClass(ItemDDAxeClass, 1);
				}
			}



		}
	}
}

