// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/DDGrassOne.h"
#include "Collision/DDCollision.h"
#include "Engine/EngineTypes.h"
#include "Interface/DDItemInteractionInterface.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Character/DDCharacterPlayer.h"
#include "Item/DDItemWaterBottle.h"

// Sets default values
ADDGrassOne::ADDGrassOne()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerGrassOne = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	GrassOne = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tent"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = TriggerGrassOne;
	GrassOne->SetupAttachment(TriggerGrassOne);

	TriggerGrassOne->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerGrassOne->SetBoxExtent(FVector(70.0f, 105.0f, 750.0f));
	TriggerGrassOne->SetRelativeLocation(FVector(521.0f, -16.0f, 0.0f));
	TriggerGrassOne->OnComponentBeginOverlap.AddDynamic(this, &ADDGrassOne::OnOverlapBegin);
	TriggerGrassOne->OnComponentEndOverlap.AddDynamic(this, &ADDGrassOne::OnOverlapEnd);


	static ConstructorHelpers::FObjectFinder<UStaticMesh>GrassOneMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/TropicalIsland/Meshes/SM_ElephantEarA.SM_ElephantEarA'"));
	if (GrassOneMeshRef.Object) {
		GrassOne->SetStaticMesh(GrassOneMeshRef.Object);
	}

}

// Called when the game starts or when spawned
void ADDGrassOne::BeginPlay()
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

// Called every frame
void ADDGrassOne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADDGrassOne::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ItemWidget->SetVisibility(ESlateVisibility::Visible);

	PlayerActor = OtherActor;
}

void ADDGrassOne::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);
	PlayerActor = nullptr;
}

void ADDGrassOne::OnInteract()
{
	if (ItemWidget->IsVisible())
	{
		ADDCharacterPlayer* Pawn = Cast<ADDCharacterPlayer>(PlayerActor);
		if (!Pawn)
		{
			return;
		}

		UStaticMeshComponent* Bottle = Pawn->EquipmentWaterBottle;
		if (!Bottle)
		{
			return;
		}

	}


}

