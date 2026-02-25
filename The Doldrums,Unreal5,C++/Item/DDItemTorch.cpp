// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DDItemTorch.h"
#include "Components/BoxComponent.h"
#include "Collision/DDCollision.h"
#include "Engine/EngineTypes.h"
#include "Interface/DDCharacterItemInterface.h"
#include "State/DDPlayerState.h"
#include "Components/WidgetComponent.h"
#include "NarrativeItem.h"

// Sets default values
ADDItemTorch::ADDItemTorch()
{
	TriggerTorch = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	Torch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Torch"));
	Cloth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cloth"));
	Lope = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lope"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));


	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = TriggerTorch;
	Torch->SetupAttachment(TriggerTorch);
	Cloth->SetupAttachment(TriggerTorch);
	Lope->SetupAttachment(TriggerTorch);


	TriggerTorch->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerTorch->SetBoxExtent(FVector(20.0f, 50.0f, 70.0f));
	TriggerTorch->OnComponentBeginOverlap.AddDynamic(this, &ADDItemTorch::OnOverlapBegin);
	TriggerTorch->OnComponentEndOverlap.AddDynamic(this, &ADDItemTorch::OnOverlapEnd);


	static ConstructorHelpers::FObjectFinder<UStaticMesh>TorchBodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Prop/Torch/Object_4.Object_4'"));
	if (TorchBodyMeshRef.Object) {
		Torch->SetStaticMesh(TorchBodyMeshRef.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ClothMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Prop/Torch/Object_3.Object_3'"));
	if (ClothMeshRef.Object) {
		Cloth->SetStaticMesh(ClothMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>LopeMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Prop/Torch/Object_2.Object_2'"));
	if (LopeMeshRef.Object) {
		Lope->SetStaticMesh(LopeMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UDDItemDataAsset>TorchDataAssetRef(TEXT("/Script/TheDoldrums.DDEquipmentItemData'/Game/Item/Equipment/DDIW_Torch.DDIW_Torch'"));
	if (TorchDataAssetRef.Succeeded())
	{
		Item = TorchDataAssetRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UNarrativeItem>InvTorchDataAssetRef(TEXT("/Game/Item/Equipment/BPI_Torch.BPI_Torch_C"));
	if (InvTorchDataAssetRef.Succeeded())
	{
		ItemDDTorchClass = InvTorchDataAssetRef.Class;
	}

	Torch->SetRelativeScale3D(FVector3d(0.7f));
	Cloth->SetRelativeScale3D(FVector3d(0.7f));
	Lope->SetRelativeScale3D(FVector3d(0.7f));

	Tags.Add(TEXT("DDItemTorch"));



}

// Called when the game starts or when spawned
void ADDItemTorch::BeginPlay()
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

void ADDItemTorch::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ItemWidget->SetVisibility(ESlateVisibility::Visible);

	PlayerActor = OtherActor;
}

void ADDItemTorch::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ADDItemTorch::OnInteract() 
{
	if (nullptr == Item)
	{

		UE_LOG(LogTemp, Warning, TEXT("Item is null"));

		Destroy();
		return;
	}

	if (ItemWidget->IsVisible())
	{
		if (PlayerActor)
		{
			Torch->SetHiddenInGame(true);
			Cloth->SetHiddenInGame(true);
			Lope->SetHiddenInGame(true);

			SetActorEnableCollision(false);

			IDDCharacterItemInterface* OverlappingPawn = Cast<IDDCharacterItemInterface>(PlayerActor);
			if (OverlappingPawn)
			{
				OverlappingPawn->TakeItem(Item);


				UE_LOG(LogTemp, Warning, TEXT("Item is not null"));

				Destroy();
			}

			APawn* Pawn = Cast<APawn>(PlayerActor);
			if (Pawn)
			{
				ADDPlayerState* MyPs = Pawn->GetPlayerState<ADDPlayerState>();
				if (MyPs && MyPs->Inventory)
				{
					MyPs->Inventory->TryAddItemFromClass(ItemDDTorchClass, 1);
				}
			}



		}
	}
}

