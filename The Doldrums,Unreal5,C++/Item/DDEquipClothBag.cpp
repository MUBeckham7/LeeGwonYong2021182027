// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DDEquipClothBag.h"
#include "Collision/DDCollision.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Interface/DDCharacterItemInterface.h"
#include "State/DDPlayerState.h"
#include "InventoryComponent.h"
#include "NarrativeItem.h"
#include "Player/DDPlayerController.h"


// Sets default values
ADDEquipClothBag::ADDEquipClothBag()
{
	TriggerBag = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	BagTie = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BagTie"));
	BagBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BagBody"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = TriggerBag;
	BagTie->SetupAttachment(TriggerBag);
	BagBody->SetupAttachment(TriggerBag);

	TriggerBag->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerBag->SetBoxExtent(FVector(70.0f, 105.0f, 750.0f));
	TriggerBag->SetRelativeLocation(FVector(521.0f, -16.0f, 0.0f));
	TriggerBag->OnComponentBeginOverlap.AddDynamic(this, &ADDEquipClothBag::OnOverlapBegin);
	TriggerBag->OnComponentEndOverlap.AddDynamic(this, &ADDEquipClothBag::OnOverlapEnd);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>BagTieMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/PostApoClothing/Meshes/MaleAverageNormal/SKM_MAN_TravelBag_Part1.SKM_MAN_TravelBag_Part1'"));
	if (BagTieMeshRef.Object) {
		BagTie->SetSkeletalMesh(BagTieMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>BagBodyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/PostApoClothing/Meshes/MaleAverageNormal/SKM_TravelBag_Part2.SKM_TravelBag_Part2'"));
	if (BagBodyMeshRef.Object) {
		BagBody->SetSkeletalMesh(BagBodyMeshRef.Object);
	}

	///Script/UMGEditor.WidgetBlueprint'/NarrativeInventory/NarrativeUI/WBP_ItemInspector.WBP_ItemInspector'
	bTakedItem = false;
}

// Called when the game starts or when spawned
void ADDEquipClothBag::BeginPlay()
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

void ADDEquipClothBag::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ItemWidget->SetVisibility(ESlateVisibility::Visible);

	PlayerActor = OtherActor;
}

void ADDEquipClothBag::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ADDEquipClothBag::OnInteract()
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
			BagTie->SetHiddenInGame(true);
			BagBody->SetHiddenInGame(true);
			SetActorEnableCollision(false);

			IDDCharacterItemInterface* OverlappingPawn = Cast<IDDCharacterItemInterface>(PlayerActor);
			if (OverlappingPawn)
			{
				OverlappingPawn->TakeItem(Item);
				bTakedItem = true;

			}

			APawn* Pawn = Cast<APawn>(PlayerActor);
			if (Pawn)
			{
				ADDPlayerState* MyPs = Pawn->GetPlayerState<ADDPlayerState>();
				if (MyPs && MyPs->Inventory)
				{
				//MyPs->Inventory->TryAddItemFromClass(ItemDataDDBag, 1);


					BagTie->DestroyComponent();
					BagBody->DestroyComponent();
				}
				ADDPlayerController* MyPc = Pawn->GetController<ADDPlayerController>();
				if (MyPc)
				{
					MyPc->BagMeshPart1 = BagBody;
				}
				

			}


		}
	}
}


