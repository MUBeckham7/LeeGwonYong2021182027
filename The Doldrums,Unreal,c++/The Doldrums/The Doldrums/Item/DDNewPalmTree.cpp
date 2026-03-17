// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DDNewPalmTree.h"
#include "Character/DDCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Interface/DDItemInteractionInterface.h"
#include "Item/DDPalm.h"
#include "TimerManager.h"


ADDNewPalmTree::ADDNewPalmTree(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	PrimaryActorTick.bCanEverTick = false;
	PalmClass = ADDPalm::StaticClass();

	TriggerTree->SetBoxExtent(FVector(70.0f, 105.0f, 750.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget> InputE(TEXT("/Game/Widget/WBP_Interact.WBP_Interact_C"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TrunkMeshRef(
		TEXT("/Script/Engine.StaticMesh'/Game/TropicalIsland/Meshes/SM_PalmTreeB.SM_PalmTreeB'")
	);
	if (TrunkMeshRef.Succeeded())
	{
		TrunkMesh = TrunkMeshRef.Object;
	}

	// 여기엔 잎, 꼭대기 장식 등 "절삭 안 되는" 메시를 넣는 구조
	// AttachmentMeshes.Add(...);

	Tags.Add(TEXT("DDPalmTree1"));
}

void ADDNewPalmTree::BeginPlay()
{
	Super::BeginPlay();

	PreviousTime = 0.0f;
	AccumulateDays = 0;
	GenerateRandomSpawnSchedule();

	GetWorld()->GetTimerManager().SetTimer(
		PalmGrowthTimerHandle,
		this,
		&ADDNewPalmTree::UpdatePalmGrowth,
		1.0f,
		true
	);
}

void ADDNewPalmTree::UpdatePalmGrowth()
{
	if (!CachedPlayer)
	{
		return;
	}

	CurrentTime = CachedPlayer->UDSTime;

	if (PreviousTime == -1.0f)
	{
		PreviousTime = CurrentTime;
		return;
	}

	if (CurrentTime < PreviousTime)
	{
		AccumulateDays++;
		UE_LOG(LogTemp, Log, TEXT("DDNewPalmTree Day Changed: %d"), AccumulateDays);

		const int32 CurrentDay = AccumulateDays;
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

void ADDNewPalmTree::OnInteract()
{
	if (!PlayerActor || !ItemWidget || !ItemWidget->IsVisible())
	{
		return;
	}

	if (IDDItemInteractionInterface* Pawn = Cast<IDDItemInteractionInterface>(PlayerActor))
	{
		Pawn->BumpPalmTreeChangeView();
	}
}

void ADDNewPalmTree::HandleTreeFelled()
{
	// 필요하면 야자수 전용 처리 추가
	// 예: 남아 있는 열매 강제 낙하
	FallFruit();

	Super::HandleTreeFelled();
}

void ADDNewPalmTree::FallFruit()
{
	if (CoconutList.IsEmpty())
	{
		return;
	}

	auto* HeadNode = CoconutList.GetHead();
	ADDPalm* FirstCoconut = HeadNode->GetValue();

	if (FirstCoconut)
	{
		FirstCoconut->bShouldFall = true;
	}

	CoconutList.RemoveNode(HeadNode);
}

void ADDNewPalmTree::GenerateRandomSpawnSchedule()
{
	SpawnDays.Empty();

	for (int32 i = 0; i < MaxPalmPerYear; i++)
	{
		SpawnDays.Add(FMath::RandRange(0, 364));
	}

	SpawnDays.Sort();
	GeneratedThisYear = 0;

	for (int32 Day : SpawnDays)
	{
		UE_LOG(LogTemp, Log, TEXT("DDNewPalmTree Spawn Scheduled Day: %d"), Day);
	}
}

void ADDNewPalmTree::SpawnPalm()
{
	if (CoconutList.Num() >= MaxPalmPerYear || !PalmClass)
	{
		return;
	}

	const FVector TreeLocation = GetActorLocation();

	const float RandomX = FMath::RandRange(50.0f, 80.0f);
	const float RandomY = FMath::RandRange(0.0f, 35.0f);
	const float RandomZ = FMath::RandRange(550.0f, 570.0f);

	const FVector SpawnLocation(
		TreeLocation.X + RandomX,
		TreeLocation.Y + RandomY,
		TreeLocation.Z + RandomZ
	);

	ADDPalm* SpawnedPalm = GetWorld()->SpawnActor<ADDPalm>(
		PalmClass,
		SpawnLocation,
		FRotator::ZeroRotator
	);

	if (SpawnedPalm)
	{
		SpawnedPalm->NewOwnerTree = this;
		CoconutList.AddTail(SpawnedPalm);
	}
}
