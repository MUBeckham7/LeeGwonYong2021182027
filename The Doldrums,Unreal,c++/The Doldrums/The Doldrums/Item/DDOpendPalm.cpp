// Fill out your copyright notice in the Description page of Project Settings.

#include "Collision/DDCollision.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/EngineTypes.h"
#include "Interface/DDCharacterItemInterface.h"
#include "Player/DDPlayerController.h"
#include "State/DDPlayerState.h"
#include "NarrativeItem.h"
#include "Player/DDPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Item/DDOpendPalm.h"

// Sets default values
ADDOpendPalm::ADDOpendPalm()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TriggerOpendPalm = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	OpendPalmPart1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PalmPart1"));
	OpendPalmPart2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PalmPart2"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = TriggerOpendPalm;
	OpendPalmPart1->SetupAttachment(TriggerOpendPalm);
	OpendPalmPart2->SetupAttachment(TriggerOpendPalm);
	Text->SetupAttachment(OpendPalmPart1);

	TriggerOpendPalm->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerOpendPalm->SetBoxExtent(FVector(15.0f, 15.0f, 10.0f));

	OpendPalmPart1->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	OpendPalmPart2->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));


	OpendPalmPart1->SetRelativeScale3D(FVector(0.14f, 0.14f, 0.14f));
	OpendPalmPart2->SetRelativeScale3D(FVector(0.14f, 0.14f, 0.14f));
	TriggerOpendPalm->OnComponentBeginOverlap.AddDynamic(this, &ADDOpendPalm::OnOverlapBeginOpendPalm);
	TriggerOpendPalm->OnComponentEndOverlap.AddDynamic(this, &ADDOpendPalm::OnOverlapEndOpendPalm);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>OpendPalmMesh1Ref(TEXT("/Script/Engine.StaticMesh'/Game/Prop/Palm/OpendPalm/Object_2.Object_2'"));
	if (OpendPalmMesh1Ref.Object) {
		OpendPalmPart1->SetStaticMesh(OpendPalmMesh1Ref.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>OpendPalmMesh2Ref(TEXT("/Script/Engine.StaticMesh'/Game/Prop/Palm/OpendPalm/Object_3.Object_3'"));
	if (OpendPalmMesh2Ref.Object) {
		OpendPalmPart2->SetStaticMesh(OpendPalmMesh2Ref.Object);
	}

	static ConstructorHelpers::FObjectFinder<UDDItemDataAsset>PalmDataAssetRef(TEXT("/Script/TheDoldrums.DDEquipmentItemData'/Game/Item/Food/DDIF_OpendPalm.DDIF_OpendPalm'"));
	if (PalmDataAssetRef.Succeeded())
	{
		Item = PalmDataAssetRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UNarrativeItem>InvPalmDataAssetRef(TEXT("/Game/Item/Food/BPI_OpendPalm.BPI_OpendPalm_C"));
	if (InvPalmDataAssetRef.Succeeded())
	{
		ItemDDOpendPalmClass = InvPalmDataAssetRef.Class;
	}

}

// Called when the game starts or when spawned
void ADDOpendPalm::BeginPlay()
{
	Super::BeginPlay();
	
	CachedPlayerController = Cast<ADDPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	InteractEnableTime = GetWorld()->GetTimeSeconds() + InteractEnableDelay;

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

void ADDOpendPalm::OnOverlapBeginOpendPalm(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (!ItemWidget || !CachedPlayerController)
		return;

	if (OtherActor != CachedPlayerController->GetPawn())
		return;

	PlayerActor = OtherActor;
	CachedPlayerController->bCanOpenInventoryNearItem = true;

	if (CachedPlayerController->bOpenInventory)
	{
		ItemWidget->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	if (GetWorld() && GetWorld()->GetTimeSeconds() < InteractEnableTime)
	{
		ItemWidget->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	ItemWidget->SetVisibility(ESlateVisibility::Visible);
}

void ADDOpendPalm::OnOverlapEndOpendPalm(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);

	if (CachedPlayerController && OtherActor == CachedPlayerController->GetPawn())
	{
		CachedPlayerController->bCanOpenInventoryNearItem = false;
		PlayerActor = nullptr;
	}

}

void ADDOpendPalm::OnInteract()
{
	if (nullptr == Item)
	{
		Destroy();
		return;
	}

	if (GetWorld() && GetWorld()->GetTimeSeconds() < InteractEnableTime)
	{
		return;
	}

	if (!CachedPlayerController)
	{
		return;
	}

	APawn* Pawn = CachedPlayerController->GetPawn();
	if (!Pawn || !TriggerOpendPalm || !TriggerOpendPalm->IsOverlappingActor(Pawn))
	{
		return;
	}

	OpendPalmPart1->SetHiddenInGame(true);
	OpendPalmPart2->SetHiddenInGame(true);
	SetActorEnableCollision(false);

	IDDCharacterItemInterface* OverlappingPawn = Cast<IDDCharacterItemInterface>(Pawn);
	if (OverlappingPawn)
	{
		OverlappingPawn->TakeItem(Item);
	}

	ADDPlayerState* MyPs = Pawn->GetPlayerState<ADDPlayerState>();
	if (MyPs && MyPs->Inventory)
	{
		MyPs->Inventory->TryAddItemFromClass(ItemDDOpendPalmClass, 1);
	}

	Destroy();
}
