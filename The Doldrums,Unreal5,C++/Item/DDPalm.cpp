// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DDPalm.h"
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
#include "Item/DDOpendPalm.h"

ADDPalm::ADDPalm()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TriggerFruit = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	Fruit = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fruit"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = Fruit;

	TriggerFruit->SetupAttachment(Fruit);
	//Fruit->SetupAttachment(TriggerFruit);
	Text->SetupAttachment(Fruit);

	TriggerFruit->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerFruit->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	Fruit->SetRelativeRotation(FRotator(-60.0f, -30.0f, 0.0f));
	Fruit->SetRelativeScale3D(FVector(0.3f,0.3f,0.3f));
	TriggerFruit->OnComponentBeginOverlap.AddDynamic(this, &ADDPalm::OnOverlapBeginFruit);
	TriggerFruit->OnComponentEndOverlap.AddDynamic(this, &ADDPalm::OnOverlapEndFruit);

	//TriggerFruit->SetRelativeLocation(FVector(102.0f, 53.0f, 575.0f));
	//Fruit->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>FruitMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Prop/Palm/coconut123.coconut123'"));
	if (FruitMeshRef.Object) {
		Fruit->SetStaticMesh(FruitMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UDDItemDataAsset>PalmDataAssetRef(TEXT("/Script/TheDoldrums.DDEquipmentItemData'/Game/Item/Food/DDIF_Palm.DDIF_Palm'"));
	if (PalmDataAssetRef.Succeeded())
	{
		Item = PalmDataAssetRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UNarrativeItem>InvPalmDataAssetRef(TEXT("/Game/Item/Food/BPI_Palm.BPI_Palm_C"));
	if (InvPalmDataAssetRef.Succeeded())
	{
		ItemDDPalmClass = InvPalmDataAssetRef.Class;
	}

	OpenPalmClass = ADDOpendPalm::StaticClass();

}

void ADDPalm::BeginPlay()
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

	UStaticMeshComponent* Mesh = Fruit;
	if (!Mesh) return;

	// simulate physics
	Mesh->SetSimulatePhysics(false);

	Fruit->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Fruit->SetCollisionResponseToAllChannels(ECR_Block);

	Fruit->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);


}

void ADDPalm::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bShouldFall && !bIsFalling)
	{
		StartFall();
	}


}

void ADDPalm::OnOverlapBeginFruit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (!ItemWidget)
		return;

	if (CachedPlayerController->bOpenInventory)
	{
		ItemWidget->SetVisibility(ESlateVisibility::Hidden);
	}


	ItemWidget->SetVisibility(ESlateVisibility::Visible);

	PlayerActor = OtherActor;

	if (CachedPlayerController && OtherActor == CachedPlayerController->GetPawn())
	{
		CachedPlayerController->bCanOpenInventoryNearItem = true;
	}

}

void ADDPalm::OnOverlapEndFruit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);

	if (CachedPlayerController && OtherActor == CachedPlayerController->GetPawn())
	{
		CachedPlayerController->bCanOpenInventoryNearItem = false;
	}
}

void ADDPalm::StartFall()
{

	bIsFalling = true;


	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	auto Mesh = FindComponentByClass<UStaticMeshComponent>();
	if (!Mesh) return;
	

	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Mesh->WakeRigidBody();

}

void ADDPalm::ReplaceWithOpenPalm()
{
	if (!GetWorld() || !OpenPalmClass)
	{
		Destroy();
		return;
	}

	const FVector SpawnLocation = GetActorLocation();
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<ADDOpendPalm>(OpenPalmClass, SpawnLocation, SpawnRotation, SpawnParams);
	Destroy();
}

void ADDPalm::OnInteract()
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
			Fruit->SetHiddenInGame(true);
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
					MyPs->Inventory->TryAddItemFromClass(ItemDDPalmClass, 1);
					UE_LOG(LogTemp, Log, TEXT("Fucking! Palm Equip"));
				}
			}



		}
	}
}
