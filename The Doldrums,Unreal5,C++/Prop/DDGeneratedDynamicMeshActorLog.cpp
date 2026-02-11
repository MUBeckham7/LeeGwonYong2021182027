// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/DDGeneratedDynamicMeshActorLog.h"
#include "Components/BoxComponent.h"
#include "MeshDescriptionToDynamicMesh.h"
#include "Item/DDEquipmentItemData.h"
#include "Character/DDCharacterBase.h"
#include "GeometryScript/MeshSubdivideFunctions.h"
#include "GeometryScript/MeshAssetFunctions.h"
#include <GeometryScript/MeshBooleanFunctions.h>
#include "GeometryScript/MeshBasicEditFunctions.h"
#include "Kismet/GameplayStatics.h"


ADDGeneratedDynamicMeshActorLog::ADDGeneratedDynamicMeshActorLog(const FObjectInitializer& ObjInit)
{
	bFrozen = true;

	DynamicMeshComp = DynamicMeshComponent;
	DynamicMeshComp->SetupAttachment(RootComponent);

	DynamicMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DynamicMeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	DynamicMeshComp->SetCollisionResponseToAllChannels(ECR_Block);
	DynamicMeshComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	DynamicMeshComp->SetGenerateOverlapEvents(true);


	DynamicMeshComp->SetNotifyRigidBodyCollision(false);
	//DynamicMeshComp->SetSimulatePhysics(true);

	//DynamicMeshComp->OnComponentHit.AddDynamic(this, &ADDGeneratedDynamicMeshActorLog::OnMeshHit);

}

void ADDGeneratedDynamicMeshActorLog::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	MarkForMeshRebuild(true, false);
}

void ADDGeneratedDynamicMeshActorLog::RebuildGeneratedMesh(UDynamicMesh* TargetMesh)
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

void ADDGeneratedDynamicMeshActorLog::OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ADDCharacterBase* Char = Cast<ADDCharacterBase>(OtherActor))
	{
		UStaticMesh* EquippedMesh = Char->EquipmentBranch->GetStaticMesh();

		if (EquippedMesh)
		{
			FName MeshName = EquippedMesh->GetFName();
			if (MeshName == FName(TEXT("simple_axe")))
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


void ADDGeneratedDynamicMeshActorLog::TickFalling()
{
FallElapsedTime += FallInterval;

    // 0.0 ~ 1.0 정규화된 진행도 t
    float t = FMath::Clamp(FallElapsedTime / FallDuration, 0.0f, 1.0f);

    // ease‑in: t^2 (처음 느리고 나중에 빨라짐). 숫자 키워서 가속 강도 조절 가능
    float eased = FMath::Pow(t, 2.0f);

    // 최종 Pitch 계산 (뒤로 쓰러질 때)
    float CurrentPitch = FMath::Lerp(FallStartRot.Pitch, FallStartRot.Pitch + FallAngle, eased);

    // 회전 적용
    FRotator NewRot = FallStartRot;
    NewRot.Pitch = CurrentPitch;
    SetActorRotation(NewRot);

    // 완료 조건: t == 1.0 에 도달하면 타이머 정리
    if (t >= 1.0f)
    {
        // 정확히 최종 회전 보정
        SetActorRotation(FallEndRot);
        GetWorld()->GetTimerManager().ClearTimer(FallTimerHandle);
    }
}


void ADDGeneratedDynamicMeshActorLog::SubtractWithTool(UStaticMeshComponent* ToolComponent, const FVector& ImpactWorldPoint)
{
	if (!ToolComponent) return;

	UStaticMesh* EquippedMesh = ToolComponent->GetStaticMesh();
	if (!EquippedMesh || EquippedMesh->GetFName() != TEXT("simple_axe"))
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

	UGeometryScriptLibrary_MeshBooleanFunctions::ApplyMeshBoolean(TargetMeshResult, TargetWorldX, AlloMesh, EqTransform, EGeometryScriptBooleanOperation::Subtract, BoolOpts, nullptr);

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
		FVector ChopDir = (GetActorLocation() - ImpactWorldPoint).GetSafeNormal2D();
		FVector Offset = ChopDir * ShakeStrength;
		SetActorLocation(OrigLoc + Offset);

		// 원위치 복귀
		FTimerHandle TmpHandle;
		GetWorld()->GetTimerManager().SetTimer(TmpHandle,FTimerDelegate::CreateLambda([this, OrigLoc]() { SetActorLocation(OrigLoc); }),ShakeDuration, false);
		return;
	}

	// 3) Falling effect only (no stump spawn)
	// Rotate over time
	if (CurrentHits >= HitsToBreak)
	{
		       // 1) 쓰러질 시작/끝 회전 설정
			        // (A) 쓰러질 사운드 재생
			if (FallSound)
			{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FallSound, GetActorLocation());
			}
		
			       // (B) 쓰러질 애니메이션 시작
		FallStartRot = GetActorRotation();
		FallEndRot = FRotator(FallStartRot.Pitch + FallAngle,FallStartRot.Yaw,FallStartRot.Roll);
		FallElapsedTime = 0.0f;


		GetWorld()->GetTimerManager().SetTimer(FallTimerHandle,this,&ADDGeneratedDynamicMeshActorLog::TickFalling,FallInterval,true);
	}
}
