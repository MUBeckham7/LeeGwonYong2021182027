// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DDItemMachete.h"
#include "Collision/DDCollision.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Interface/DDCharacterItemInterface.h"
#include "Player/DDPlayerController.h"
#include "State/DDPlayerState.h"
#include "NarrativeItem.h"
#include "Player/DDPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADDItemMachete::ADDItemMachete()
{
	TriggerMachete = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	Machete = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Machete"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = TriggerMachete;
	Machete->SetupAttachment(TriggerMachete);
	//Machete->SetRelativeScale3D(FVector(0.002f));


	TriggerMachete->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerMachete->SetBoxExtent(FVector(55.0f, 30.0f, 30.0f));
	//->SetRelativeLocation(FVector(521.0f, -16.0f, 0.0f));
	TriggerMachete->OnComponentBeginOverlap.AddDynamic(this, &ADDItemMachete::OnOverlapBegin);
	TriggerMachete->OnComponentEndOverlap.AddDynamic(this, &ADDItemMachete::OnOverlapEnd);


	static ConstructorHelpers::FObjectFinder<UStaticMesh>MacheteMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Prop/Machete/shoelace_machete.shoelace_machete'"));
	if (MacheteMeshRef.Object) {
		Machete->SetStaticMesh(MacheteMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UDDItemDataAsset>MacheteDataAssetRef(TEXT("/Script/TheDoldrums.DDEquipmentItemData'/Game/Item/Equipment/DDIW_Machete.DDIW_Machete'"));
	if (MacheteDataAssetRef.Succeeded())
	{
		Item = MacheteDataAssetRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UNarrativeItem>InvMacheteDataAssetRef(TEXT("/Game/Item/Equipment/BPI_Machete.BPI_Machete_C"));
	if (InvMacheteDataAssetRef.Succeeded())
	{
		ItemDDMacheteClass = InvMacheteDataAssetRef.Class;
	}

}

// Called when the game starts or when spawned
void ADDItemMachete::BeginPlay()
{
	Super::BeginPlay();

	CachedPlayerController = Cast<ADDPlayerController>(UGameplayStatics::GetPlayerController(this, 0));


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

void ADDItemMachete::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (!ItemWidget)
		return;

	if (CachedPlayerController->bOpenInventory)
	{
		ItemWidget->SetVisibility(ESlateVisibility::Hidden);
		return;
	}


	ItemWidget->SetVisibility(ESlateVisibility::Visible);

	PlayerActor = OtherActor;

	if (CachedPlayerController && OtherActor == CachedPlayerController->GetPawn())
	{
		CachedPlayerController->bCanOpenInventoryNearItem = true;
	}

}

void ADDItemMachete::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);

	if (CachedPlayerController && OtherActor == CachedPlayerController->GetPawn())
	{
		CachedPlayerController->bCanOpenInventoryNearItem = false;
	}
}

void ADDItemMachete::OnInteract()
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
			Machete->SetHiddenInGame(true);
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
					MyPs->Inventory->TryAddItemFromClass(ItemDDMacheteClass, 1);
				}
			}



		}
	}
}

