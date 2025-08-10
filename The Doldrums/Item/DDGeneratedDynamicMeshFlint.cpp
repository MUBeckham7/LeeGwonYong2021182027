// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DDGeneratedDynamicMeshFlint.h"
#include "Components/BoxComponent.h"
#include "MeshDescriptionToDynamicMesh.h"
#include "Item/DDEquipmentItemData.h"
#include "Character/DDCharacterBase.h"
#include "GeometryScript/MeshSubdivideFunctions.h"
#include "GeometryScript/MeshAssetFunctions.h"
#include <GeometryScript/MeshBooleanFunctions.h>

ADDGeneratedDynamicMeshFlint::ADDGeneratedDynamicMeshFlint(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	bFrozen = true;

	DynamicMeshComp = DynamicMeshComponent;
	DynamicMeshComp->SetupAttachment(RootComponent);

	DynamicMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DynamicMeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	DynamicMeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	DynamicMeshComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	DynamicMeshComp->SetGenerateOverlapEvents(true);

	DynamicMeshComp->SetNotifyRigidBodyCollision(false);
	//DynamicMeshComp->SetSimulatePhysics(true);

	DynamicMeshComp->OnComponentHit.AddDynamic(this, &ADDGeneratedDynamicMeshFlint::OnMeshHit);
	//DynamicMeshComp->OnComponentBeginOverlap.AddDynamic(this, &ADDGeneratedDynamicMeshFlint::OnMeshBeginOverlap);

}


void ADDGeneratedDynamicMeshFlint::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	MarkForMeshRebuild(true, false);
}

void ADDGeneratedDynamicMeshFlint::RebuildGeneratedMesh(UDynamicMesh* TargetMesh)
{
	Super::RebuildGeneratedMesh(TargetMesh);

	if (LogMesh == nullptr)
	{
		return;
	}

	////////////////////////////////////////////////////////////////////////	매쉬 불러오고 머터리얼 입히기
	
	FDynamicMesh3* DynMesh3 = TargetMesh->GetMeshPtr();
	DynMesh3->Clear();

	if (const FMeshDescription* MeshDesc = LogMesh->GetMeshDescription(0))
	{
		FMeshDescriptionToDynamicMesh Converter;
		Converter.Convert(MeshDesc, *DynMesh3);
	}


	DynamicMeshComp = DynamicMeshComponent;
	if (DynamicMeshComp == nullptr)
	{
		return;
	}
	

	const TArray<FStaticMaterial>& Mats = LogMesh->GetStaticMaterials();
	int32 NumtoCopy = FMath::Min(Mats.Num(), 2);
	for (int32 SlotIdx = 0; SlotIdx < NumtoCopy; ++SlotIdx)
	{
		UMaterialInterface* Mat = Mats[SlotIdx].MaterialInterface;
		if (Mat)
		{
			DynamicMeshComp->SetMaterial(SlotIdx, Mat);
		}
	}
	////////////////////////////////////////////////////////////////////////

	UDynamicMesh* DynMesh = DynamicMeshComp->GetDynamicMesh();

	FGeometryScriptPNTessellateOptions TessOptions;


	int32 TessLevel = 2;

	UGeometryScriptLibrary_MeshSubdivideFunctions::ApplyPNTessellation(DynMesh, TessOptions, TessLevel);

	TargetMeshResult = DynMesh;

	DynamicMeshComp->EnableComplexAsSimpleCollision();

	DynamicMeshComp->NotifyMeshUpdated();
	DynamicMeshComp->UpdateCollision(false);

}

void ADDGeneratedDynamicMeshFlint::OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ADDCharacterBase* Char = Cast<ADDCharacterBase>(OtherActor))
	{
		UStaticMesh* EquippedMesh = Char->EquipmentBranch->GetStaticMesh();

		if (EquippedMesh)
		{
			FName MeshName = EquippedMesh->GetFName();
			if (MeshName == FName(TEXT("SM_StickB05")))
			{
				FTransform EqTransform = Char->EquipmentBranch->GetComponentTransform();
				FVector LocalHit = EqTransform.InverseTransformPosition(Hit.ImpactPoint);
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("Hit Equipment! Local Pos: %s"), *LocalHit.ToString()));
				}

				UDynamicMesh* AlloMesh = AllocateComputeMesh();

				FGeometryScriptCopyMeshFromAssetOptions CopyOpts;
				FGeometryScriptMeshReadLOD ReadLOD;
				EGeometryScriptOutcomePins OutCome;
				UGeometryScriptLibrary_StaticMeshFunctions::CopyMeshFromStaticMesh(EquippedMesh, AlloMesh, CopyOpts, ReadLOD, OutCome, nullptr);

				if (OutCome != EGeometryScriptOutcomePins::Success) {
					ReleaseComputeMesh(AlloMesh);

					return;
				}

				FTransform TargetX = GetActorTransform();
				FTransform ToolLocalX = Char->EquipmentBranch->GetComponentTransform();


				FGeometryScriptMeshBooleanOptions BoolOpts;
				UGeometryScriptLibrary_MeshBooleanFunctions::ApplyMeshBoolean(TargetMeshResult, TargetX, AlloMesh, ToolLocalX, EGeometryScriptBooleanOperation::Subtract, BoolOpts, nullptr);

				//DynamicMeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
				//DynamicMeshComp->SetGenerateOverlapEvents(true);

				DynamicMeshComp->NotifyMeshUpdated();
				DynamicMeshComp->UpdateCollision(false);


				ReleaseComputeMesh(AlloMesh);

				DynamicMeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
				DynamicMeshComp->SetGenerateOverlapEvents(true);
				DynamicMeshComp->SetNotifyRigidBodyCollision(false);

			}
		}
	}
}

void ADDGeneratedDynamicMeshFlint::SubtractWithTool(UStaticMeshComponent* ToolComponent, const FVector& ImpactWorldPoint)
{
	if (!ToolComponent) return;

	UStaticMesh* EquippedMesh = ToolComponent->GetStaticMesh();
	if (!EquippedMesh || EquippedMesh->GetFName() != TEXT("SM_StickB05"))
		return;

	FTransform EqTransform = ToolComponent->GetComponentTransform();
	FVector LocalHit = EqTransform.InverseTransformPosition(ImpactWorldPoint);

	UDynamicMesh* AlloMesh = AllocateComputeMesh();
	FGeometryScriptCopyMeshFromAssetOptions CopyOpts;
	FGeometryScriptMeshReadLOD ReadLOD;
	EGeometryScriptOutcomePins CopyOutcome;

	UGeometryScriptLibrary_StaticMeshFunctions::CopyMeshFromStaticMesh(EquippedMesh, AlloMesh, CopyOpts, ReadLOD, CopyOutcome, nullptr);


	if (CopyOutcome != EGeometryScriptOutcomePins::Success) {
		ReleaseComputeMesh(AlloMesh);
		return;
	}

	FTransform TargetWorldX = GetActorTransform();
	FTransform ToolLocalX = TargetWorldX.Inverse() * EqTransform;
	FGeometryScriptMeshBooleanOptions BoolOpts;

	UGeometryScriptLibrary_MeshBooleanFunctions::ApplyMeshBoolean(TargetMeshResult,TargetWorldX,AlloMesh,EqTransform,EGeometryScriptBooleanOperation::Subtract,BoolOpts,nullptr);

	ReleaseComputeMesh(AlloMesh);

	DynamicMeshComp->NotifyMeshUpdated();
	DynamicMeshComp->UpdateCollision(false);

	// 7) restore your overlap settings if you like
	DynamicMeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	DynamicMeshComp->SetGenerateOverlapEvents(true);
	DynamicMeshComp->SetNotifyRigidBodyCollision(false);

}
