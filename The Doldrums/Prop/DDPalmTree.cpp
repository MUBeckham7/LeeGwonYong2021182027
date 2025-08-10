// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/DDPalmTree.h"
#include "Components/BoxComponent.h"
#include "Collision/DDCollision.h"
#include "Engine/EngineTypes.h"
#include "Interface/DDItemInteractionInterface.h"
#include "Components/WidgetComponent.h"


ADDPalmTree::ADDPalmTree()
{

	TriggerTree = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	TriggerFruit = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox2"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Fruit = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fruit"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}


	RootComponent = TriggerTree;
	Body->SetupAttachment(TriggerTree);

	TriggerTree->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerTree->SetBoxExtent(FVector(70.0f, 105.0f, 750.0f));
	TriggerTree->SetRelativeLocation(FVector(521.0f, -16.0f, 0.0f));
	TriggerTree->OnComponentBeginOverlap.AddDynamic(this,&ADDPalmTree::OnOverlapBegin);
	TriggerTree->OnComponentEndOverlap.AddDynamic(this, &ADDPalmTree::OnOverlapEnd);

	Fruit->SetupAttachment(TriggerTree);
	Fruit->SetRelativeLocation(FVector(102.0f, 40.0f, 569.0f));
	Fruit->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	TriggerFruit->SetupAttachment(Fruit);



	TriggerFruit->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerFruit->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	TriggerFruit->OnComponentBeginOverlap.AddDynamic(this, &ADDPalmTree::OnOverlapBeginFruit);



	static ConstructorHelpers::FObjectFinder<UStaticMesh>BodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/TropicalIsland/Meshes/SM_PalmTreeB.SM_PalmTreeB'"));
	if (BodyMeshRef.Object) {
		Body->SetStaticMesh(BodyMeshRef.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>FruitMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Prop/Palm/coconut123.coconut123'"));
	if (FruitMeshRef.Object) {
		Fruit->SetStaticMesh(FruitMeshRef.Object);
	}

	Tags.Add(TEXT("DDPalmTree1"));

}

void ADDPalmTree::BeginPlay()
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


void ADDPalmTree::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ItemWidget->SetVisibility(ESlateVisibility::Visible);

		//if (Body)
		//{
		//	IDDItemInteractionInterface* Palmtree = Cast<IDDItemInteractionInterface>(Body->GetOwner());
		//	if (Palmtree)
		//	{
		//		Palmtree->ItemOverlapCheck();
		//	}
		//};
		PlayerActor = OtherActor;
}

void ADDPalmTree::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);
	PlayerActor = NULL;
}

void ADDPalmTree::OnOverlapBeginFruit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	Fruit->SetHiddenInGame(true);

}

void ADDPalmTree::OnInteract()
{
	if (ItemWidget->IsVisible())
	{

		if (PlayerActor)
		{


			IDDItemInteractionInterface* Pawn = Cast<IDDItemInteractionInterface>(PlayerActor);
			if (Pawn)
			{

				Pawn->BumpPalmTreeChangeView();		
				/*Fruit->SetSimulatePhysics(true);
				Fruit->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
				Fruit->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);*/
			}
		}
	}

}

