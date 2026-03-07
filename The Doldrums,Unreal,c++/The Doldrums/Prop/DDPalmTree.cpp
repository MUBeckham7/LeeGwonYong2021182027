// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/DDPalmTree.h"
#include "Components/BoxComponent.h"
#include "Collision/DDCollision.h"
#include "Engine/EngineTypes.h"
#include "Interface/DDItemInteractionInterface.h"
#include "Components/WidgetComponent.h"
#include "Character/DDCharacterBase.h"
#include "Item/DDPalm.h"
#include "Containers/Queue.h"


ADDPalmTree::ADDPalmTree()
{
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TriggerTree = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));
	PalmClass = ADDPalm::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	TriggerTree->SetupAttachment(RootComponent);
	Body->SetupAttachment(TriggerTree);


	TriggerTree->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerTree->SetBoxExtent(FVector(70.0f, 105.0f, 750.0f));
	TriggerTree->OnComponentBeginOverlap.AddDynamic(this,&ADDPalmTree::OnOverlapBegin);
	TriggerTree->OnComponentEndOverlap.AddDynamic(this, &ADDPalmTree::OnOverlapEnd);


	static ConstructorHelpers::FObjectFinder<UStaticMesh>BodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/TropicalIsland/Meshes/SM_PalmTreeB.SM_PalmTreeB'"));
	if (BodyMeshRef.Object) {
		Body->SetStaticMesh(BodyMeshRef.Object);
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

	APlayerController* Pc = GetWorld()->GetFirstPlayerController();
	if (Pc)
	{
		CachedPlayer = Cast<ADDCharacterBase>(Pc->GetCharacter());
	}

	PreviousTime = 0.0f;
	AccumulateDays = 0.0f;

	GenerateRandomSpawnSchedule();

}

void ADDPalmTree::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!CachedPlayer) return;

	CurrentTime = CachedPlayer->UDSTime;      //0~2400

	if (PreviousTime == -1.0f)
	{
		PreviousTime = CurrentTime;

		return;
	}


	if ( CurrentTime < PreviousTime)
	{

		AccumulateDays++;

		UE_LOG(LogTemp, Log, TEXT("%d"), AccumulateDays);

		int32 CurrentDay = (int32)AccumulateDays;

		if (CurrentDay >= 365)
		{
			AccumulateDays = 0;
			GenerateRandomSpawnSchedule();
			GeneratedThisYear = 0;
		}
		if (SpawnDays.Contains(CurrentDay) && GeneratedThisYear < MaxPalmPerYear)
		{
			SpawnPalm();
			GeneratedThisYear++;
		}
	}
	PreviousTime = CurrentTime;
}


void ADDPalmTree::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	ItemWidget->SetVisibility(ESlateVisibility::Visible);

	PlayerActor = OtherActor;
}

void ADDPalmTree::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);
	PlayerActor = NULL;
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
			}
		}
	}

}



void ADDPalmTree::FallFruit()
{
	//Fruit->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
//	TriggerFruit->SetSimulatePhysics(true);
	//TriggerFruit->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);


	if (CoconutList.IsEmpty()) return;


	auto* HeadNode = CoconutList.GetHead();
	ADDPalm* FirstCoconut = HeadNode->GetValue();

	if (FirstCoconut)
	{
		FirstCoconut->bShouldFall = true;
	}


	CoconutList.RemoveNode(HeadNode);

	UE_LOG(LogTemp, Warning, TEXT("FallFruit"));

}

void ADDPalmTree::GenerateRandomSpawnSchedule()
{
	SpawnDays.Empty();

	for (int32 i = 0; i < MaxPalmPerYear; i++)
	{
		int32 RandomDay = FMath::RandRange(0, 364);

		SpawnDays.Add(RandomDay);
	}


	SpawnDays.Sort();

	GeneratedThisYear = 0;

	for (int32 Day : SpawnDays)
	{
		UE_LOG(LogTemp, Warning, TEXT("- Spawn Day: %d"), Day);
	}

}

void ADDPalmTree::SpawnPalm()
{

	if (CoconutList.Num() >= MaxPalmPerYear) return;

	if (!PalmClass) return;

	// 나무 기준 위치
	FVector TreeLocation = GetActorLocation();

	// ---- 랜덤 각도 (0~360도) ----
	float RandomAngle = FMath::RandRange(0.0f, 360.0f);

	float RandomX = FMath::RandRange(50.0f, 80.0f);
	float RandomY = FMath::RandRange(0.0f, 35.0f);
	float RandomZ = FMath::RandRange(550.0f, 570.0f);

	// ---- 원 좌표 계산 ----
	float Rad = FMath::DegreesToRadians(RandomAngle);

	FVector SpawnLocation = FVector(
		TreeLocation.X + RandomX,
		TreeLocation.Y + RandomY,
		TreeLocation.Z + RandomZ
	);

	FRotator SpawnRotation = FRotator::ZeroRotator;

	// ---- 실제 Palm 생성 ----
	ADDPalm* SpawnedPalm = GetWorld()->SpawnActor<ADDPalm>(PalmClass, SpawnLocation, SpawnRotation);
	if (SpawnedPalm)
	{
		//SpawnedPalm->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		SpawnedPalm->OwnerTree = this;

		CoconutList.AddTail(SpawnedPalm);
	}
}

