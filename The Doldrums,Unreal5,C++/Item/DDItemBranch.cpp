// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/DDItemBranch.h"
#include "Collision/DDCollision.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Interface/DDCharacterItemInterface.h"
#include "State/DDPlayerState.h"
#include "NarrativeItem.h"

// Sets default values
ADDItemBranch::ADDItemBranch()
{
	TriggerBranch = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	Branch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Branch"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = TriggerBranch;
	Branch->SetupAttachment(TriggerBranch);

	TriggerBranch->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerBranch->SetBoxExtent(FVector(70.0f, 105.0f, 750.0f));
	//->SetRelativeLocation(FVector(521.0f, -16.0f, 0.0f));
	TriggerBranch->OnComponentBeginOverlap.AddDynamic(this, &ADDItemBranch::OnOverlapBegin);
	TriggerBranch->OnComponentEndOverlap.AddDynamic(this, &ADDItemBranch::OnOverlapEnd);


	static ConstructorHelpers::FObjectFinder<UStaticMesh>BranchMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/TropicalIsland/Meshes/SM_StickB05.SM_StickB05'"));
	if (BranchMeshRef.Object) {
		Branch->SetStaticMesh(BranchMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UDDItemDataAsset>BranchDataAssetRef(TEXT("/Script/TheDoldrums.DDEquipmentItemData'/Game/Item/Equipment/DDIW_Branch.DDIW_Branch'"));
	if (BranchDataAssetRef.Succeeded())
	{
		Item = BranchDataAssetRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UNarrativeItem>InvBranchDataAssetRef(TEXT("/Game/Item/Equipment/BPI_Branch.BPI_Branch_C"));
	if (InvBranchDataAssetRef.Succeeded())
	{
		ItemDDBranchClass = InvBranchDataAssetRef.Class;
	}
}

void ADDItemBranch::BeginPlay()
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

void ADDItemBranch::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ItemWidget->SetVisibility(ESlateVisibility::Visible);

	PlayerActor = OtherActor;
}

void ADDItemBranch::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);

}

void ADDItemBranch::OnInteract()
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
			Branch->SetHiddenInGame(true);
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
					MyPs->Inventory->TryAddItemFromClass(ItemDDBranchClass, 1);
				}
			}



		}
	}
}
