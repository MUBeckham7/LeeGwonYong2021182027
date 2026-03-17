// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DDGDTreeBase.h"
#include "Character/DDCharacterBase.h"
#include "Collision/DDCollision.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GeometryScript/MeshSubdivideFunctions.h"
#include "GeometryScript/MeshAssetFunctions.h"
#include <GeometryScript/MeshBooleanFunctions.h>
#include "GeometryScript/MeshBasicEditFunctions.h"
#include "Item/DDEquipmentItemData.h"
#include "Kismet/GameplayStatics.h"
#include "MeshDescriptionToDynamicMesh.h"

ADDGDTreeBase::ADDGDTreeBase(const FObjectInitializer& ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;
	bFrozen = true;

	TreeRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TreeRoot"));
	SetRootComponent(TreeRoot);

	TriggerTree = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerTree"));
	TriggerTree->SetupAttachment(TreeRoot);

	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));
	Text->SetupAttachment(TreeRoot);

	DynamicMeshComp = DynamicMeshComponent;
	DynamicMeshComp->SetupAttachment(TreeRoot);

	TriggerTree->SetCollisionProfileName(CPROFILE_DDTRIGGER);
	TriggerTree->OnComponentBeginOverlap.AddDynamic(this, &ADDGDTreeBase::OnOverlapBegin);
	TriggerTree->OnComponentEndOverlap.AddDynamic(this, &ADDGDTreeBase::OnOverlapEnd);

	DynamicMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DynamicMeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	DynamicMeshComp->SetCollisionResponseToAllChannels(ECR_Block);
	DynamicMeshComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	DynamicMeshComp->SetGenerateOverlapEvents(true);
	DynamicMeshComp->SetNotifyRigidBodyCollision(false);
}

void ADDGDTreeBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ClearStaticAttachments();
	BuildStaticAttachments();
	MarkForMeshRebuild(true, false);
}

void ADDGDTreeBase::BeginPlay()
{
	Super::BeginPlay();

	SetupInteractionWidget();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		CachedPlayer = Cast<ADDCharacterBase>(PC->GetCharacter());
	}
}

void ADDGDTreeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ADDGDTreeBase::RebuildGeneratedMesh(UDynamicMesh* TargetMesh)
{
	Super::RebuildGeneratedMesh(TargetMesh);
	ApplySourceMeshToDynamicMesh(TargetMesh);
}

void ADDGDTreeBase::HandleTreeFelled()
{
	if (FallSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FallSound, GetActorLocation());
	}

	FallStartRot = GetActorRotation();
	FallEndRot = FRotator(
		FallStartRot.Pitch + FallAngle,
		FallStartRot.Yaw,
		FallStartRot.Roll
	);

	FallElapsedTime = 0.0f;

	GetWorld()->GetTimerManager().SetTimer(
		FallTimerHandle,
		this,
		&ADDGDTreeBase::TickFalling,
		FallInterval,
		true
	);
}

void ADDGDTreeBase::BuildStaticAttachments()
{
	for (int32 Index = 0; Index < AttachmentMeshes.Num(); ++Index)
	{
		if (!AttachmentMeshes[Index])
		{
			continue;
		}

		FName CompName = *FString::Printf(TEXT("Attachment_%d"), Index);
		UStaticMeshComponent* NewComp = NewObject<UStaticMeshComponent>(this, CompName);
		if (!NewComp)
		{
			continue;
		}

		NewComp->SetStaticMesh(AttachmentMeshes[Index]);
		NewComp->SetupAttachment(TreeRoot);
		NewComp->RegisterComponent();

		StaticAttachments.Add(NewComp);
	}
}

void ADDGDTreeBase::ClearStaticAttachments()
{
	for (UStaticMeshComponent* Comp : StaticAttachments)
	{
		if (Comp)
		{
			Comp->DestroyComponent();
		}
	}
	StaticAttachments.Empty();
}

void ADDGDTreeBase::TickFalling()
{
	FallElapsedTime += FallInterval;

	const float T = FMath::Clamp(FallElapsedTime / FallDuration, 0.0f, 1.0f);
	const float Eased = FMath::Pow(T, 2.0f);
	const float CurrentPitch = FMath::Lerp(FallStartRot.Pitch, FallStartRot.Pitch + FallAngle, Eased);

	FRotator NewRot = FallStartRot;
	NewRot.Pitch = CurrentPitch;
	SetActorRotation(NewRot);

	if (T >= 1.0f)
	{
		SetActorRotation(FallEndRot);
		GetWorld()->GetTimerManager().ClearTimer(FallTimerHandle);
	}
}

void ADDGDTreeBase::SetupInteractionWidget()
{
	if (!InteractionItemWidgetClass)
	{
		return;
	}

	ItemWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionItemWidgetClass);
	if (ItemWidget)
	{
		ItemWidget->AddToViewport();
		ItemWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ADDGDTreeBase::ApplySourceMeshToDynamicMesh(UDynamicMesh* TargetMesh)
{
	if (!TrunkMesh || !TargetMesh)
	{
		return;
	}

	FDynamicMesh3* DynMesh3 = TargetMesh->GetMeshPtr();
	DynMesh3->Clear();

	if (const FMeshDescription* MeshDesc = TrunkMesh->GetMeshDescription(0))
	{
		FMeshDescriptionToDynamicMesh Converter;
		Converter.Convert(MeshDesc, *DynMesh3);
	}

	const TArray<FStaticMaterial>& Mats = TrunkMesh->GetStaticMaterials();
	for (int32 SlotIdx = 0; SlotIdx < Mats.Num(); ++SlotIdx)
	{
		if (Mats[SlotIdx].MaterialInterface)
		{
			DynamicMeshComp->SetMaterial(SlotIdx, Mats[SlotIdx].MaterialInterface);
		}
	}

	UDynamicMesh* DynMesh = DynamicMeshComp->GetDynamicMesh();

	FGeometryScriptPNTessellateOptions TessOptions;
	UGeometryScriptLibrary_MeshSubdivideFunctions::ApplyPNTessellation(DynMesh, TessOptions, 2);

	TargetMeshResult = DynMesh;
	DynamicMeshComp->EnableComplexAsSimpleCollision();
	DynamicMeshComp->NotifyMeshUpdated();
	DynamicMeshComp->UpdateCollision(false);
}

void ADDGDTreeBase::SubtractWithTool(UStaticMeshComponent* ToolComponent, const FVector& ImpactWorldPoint)
{
	if (!ToolComponent || !TargetMeshResult)
	{
		return;
	}

	UStaticMesh* EquippedMesh = ToolComponent->GetStaticMesh();
	if (!EquippedMesh || EquippedMesh->GetFName() != TEXT("simple_axe"))
	{
		return;
	}

	UDynamicMesh* AlloMesh = AllocateComputeMesh();

	FGeometryScriptCopyMeshFromAssetOptions CopyOpts;
	FGeometryScriptMeshReadLOD ReadLOD;
	EGeometryScriptOutcomePins CopyOutcome;

	UGeometryScriptLibrary_StaticMeshFunctions::CopyMeshFromStaticMesh(
		EquippedMesh, AlloMesh, CopyOpts, ReadLOD, CopyOutcome, nullptr);

	if (CopyOutcome != EGeometryScriptOutcomePins::Success)
	{
		ReleaseComputeMesh(AlloMesh);
		return;
	}

	FGeometryScriptMeshBooleanOptions BoolOpts;
	UGeometryScriptLibrary_MeshBooleanFunctions::ApplyMeshBoolean(
		TargetMeshResult,
		GetActorTransform(),
		AlloMesh,
		ToolComponent->GetComponentTransform(),
		EGeometryScriptBooleanOperation::Subtract,
		BoolOpts,
		nullptr
	);

	ReleaseComputeMesh(AlloMesh);

	DynamicMeshComp->NotifyMeshUpdated();
	DynamicMeshComp->UpdateCollision(false);
	DynamicMeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	DynamicMeshComp->SetGenerateOverlapEvents(true);
	DynamicMeshComp->SetNotifyRigidBodyCollision(true);

	CurrentHits++;
	if (CurrentHits < HitsToBreak)
	{
		const FVector OrigLoc = GetActorLocation();
		const FVector ChopDir = (GetActorLocation() - ImpactWorldPoint).GetSafeNormal2D();
		const FVector Offset = ChopDir * ShakeStrength;

		SetActorLocation(OrigLoc + Offset);

		FTimerHandle TmpHandle;
		GetWorld()->GetTimerManager().SetTimer(
			TmpHandle,
			FTimerDelegate::CreateLambda([this, OrigLoc]() { SetActorLocation(OrigLoc); }),
			ShakeDuration,
			false
		);
		return;
	}

	HandleTreeFelled();
}

void ADDGDTreeBase::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepHitResult)
{
	PlayerActor = OtherActor;

	if (ItemWidget)
	{
		ItemWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ADDGDTreeBase::OnOverlapEnd(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	PlayerActor = nullptr;

	if (ItemWidget)
	{
		ItemWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ADDGDTreeBase::OnInteract()
{
}
