// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DDEquippableItem_Backpack.h"
#include "Item/DDEquipmentComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Pawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkinnedAssetCommon.h"

#define LOCTEXT_NAMESPACE "EquippableItem"

UDDEquippableItem::UDDEquippableItem()
{
	UseActionText = LOCTEXT("UseActionText_Equippable", "Equip");
	bStackable = false;
	bCanActivate = true;
	bToggleActiveOnUse = true;
	Weight = 1.f;
}

void UDDEquippableItem::HandleEquip_Implementation()
{
}

void UDDEquippableItem::HandleUnequip_Implementation()
{
}



void UDDEquippableItem::Deactivated_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("DeActivated_Implementation called!"));
	if (GetOwningPawn())
	{
		UseActionText = LOCTEXT("EquipText", "Equip");

		if (UDDEquipmentComponent* DDEquipmentComponent = Cast<UDDEquipmentComponent>(GetOwningPawn()->GetComponentByClass(UDDEquipmentComponent::StaticClass())))
		{
			UE_LOG(LogTemp, Warning, TEXT("UDDEquipmentComponent found, equipping item!"));
			DDEquipmentComponent->DDUnequipItem(this);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UDDEquipmentComponent not found!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GetOwningPawn() is null!"));
	}
}

void UDDEquippableItem::Activated_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Activated_Implementation called!"));
	if (GetOwningPawn())
	{
		UseActionText = LOCTEXT("UnequipText", "Unequip");

		if (UDDEquipmentComponent* DDEquipmentComponent = Cast<UDDEquipmentComponent>(GetOwningPawn()->GetComponentByClass(UDDEquipmentComponent::StaticClass())))
		{
			UE_LOG(LogTemp, Warning, TEXT("UDDEquipmentComponent found, equipping item!"));
			DDEquipmentComponent->DDEquipItem(this);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UDDEquipmentComponent not found!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GetOwningPawn() is null!"));
	}
	
}

UDDEquippableItem_Backpack::UDDEquippableItem_Backpack()
{
	bShouldSetLeaderPose = true;
}

void UDDEquippableItem_Backpack::HandleEquip_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("Entered HandleEquip_Implementation()"));

    if (UDDEquipmentComponent* DDEquipmentComponent = Cast<UDDEquipmentComponent>(GetOwningPawn()->GetComponentByClass(UDDEquipmentComponent::StaticClass())))
    {
        UE_LOG(LogTemp, Warning, TEXT("Found DDEquipmentComponent"));

        if (ClothingMesh1 && DDEquipmentComponent->DDEquippableComponents.Contains(DDEquippableSlot))
        {
            UE_LOG(LogTemp, Warning, TEXT("ClothingMesh1 exists and DDEquippableSlot is valid"));

            if (USkeletalMeshComponent* SlotComponent = *DDEquipmentComponent->DDEquippableComponents.Find(DDEquippableSlot))
            {
                UE_LOG(LogTemp, Warning, TEXT("Found SlotComponent"));

                SlotComponent->SetSkeletalMesh(ClothingMesh1);
                UE_LOG(LogTemp, Warning, TEXT("ClothingMesh1 equipped"));

                int32 Idx = 0;
                for (auto& Mat : ClothingMaterials)
                {
                    SlotComponent->SetMaterial(Idx, Mat);
                    UE_LOG(LogTemp, Warning, TEXT("Set material %d to SlotComponent"), Idx);
                    ++Idx;
                }

                // ClothingMesh2 처리
                if (ClothingMesh2)
                {
                    UE_LOG(LogTemp, Warning, TEXT("ClothingMesh2 exists"));

                    // 기존 컴포넌트 제거
                    if (ClothingMesh2Component)
                    {
                        ClothingMesh2Component->DestroyComponent();
                        ClothingMesh2Component = nullptr;
                        UE_LOG(LogTemp, Warning, TEXT("Destroyed previous ClothingMesh2Component"));
                    }

                    // 동적 생성 및 Attach
                    ClothingMesh2Component = NewObject<USkeletalMeshComponent>(SlotComponent->GetOwner());
                    if (ClothingMesh2Component)
                    {
                        ClothingMesh2Component->RegisterComponent();
                        ClothingMesh2Component->SetSkeletalMesh(ClothingMesh2);
                        ClothingMesh2Component->AttachToComponent(SlotComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

                        ClothingMesh2Component->SetRelativeLocation(FVector::ZeroVector);

                        UE_LOG(LogTemp, Warning, TEXT("Created and attached ClothingMesh2Component"));

                        if (DDEquipmentComponent->LeaderPoseComponent && bShouldSetLeaderPose)
                        {
                            ClothingMesh2Component->SetLeaderPoseComponent(DDEquipmentComponent->LeaderPoseComponent);
                            UE_LOG(LogTemp, Warning, TEXT("Set LeaderPoseComponent for ClothingMesh2Component"));
                        }

                        ClothingMesh2Component->SetVisibility(true); // 혹시나 숨겨질 경우를 위해
                    }
                    else
                    {
                        UE_LOG(LogTemp, Error, TEXT("Failed to create ClothingMesh2Component"));
                    }
                }

                if (DDEquipmentComponent->LeaderPoseComponent)
                {
                    SlotComponent->SetLeaderPoseComponent(bShouldSetLeaderPose ? DDEquipmentComponent->LeaderPoseComponent : nullptr);
                    UE_LOG(LogTemp, Warning, TEXT("Set LeaderPoseComponent for SlotComponent"));
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Could not find SlotComponent"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("ClothingMesh1 is missing or DDEquippableSlot is invalid"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Could not find DDEquipmentComponent"));
    }

}

void UDDEquippableItem_Backpack::HandleUnequip_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("Entered HandleUnequip_Implementation()"));

    if (UDDEquipmentComponent* DDEquipmentComponent = Cast<UDDEquipmentComponent>(GetOwningPawn()->GetComponentByClass(UDDEquipmentComponent::StaticClass())))
    {
        UE_LOG(LogTemp, Warning, TEXT("Found DDEquipmentComponent"));

        if (DDEquipmentComponent->DDEquippableComponents.Contains(DDEquippableSlot))
        {
            if (USkeletalMeshComponent* SlotComponent = *DDEquipmentComponent->DDEquippableComponents.Find(DDEquippableSlot))
            {
                UE_LOG(LogTemp, Warning, TEXT("Found SlotComponent, unequipping SkeletalMesh"));

                SlotComponent->SetSkeletalMesh(nullptr);

                // ClothingMesh2Component 제거
                if (ClothingMesh2Component)
                {
                    ClothingMesh2Component->DestroyComponent();
                    ClothingMesh2Component = nullptr;
                    UE_LOG(LogTemp, Warning, TEXT("Destroyed ClothingMesh2Component"));
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Could not find SlotComponent (Unequip)"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("DDEquippableSlot is not in DDEquippableComponents (Unequip)"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Could not find DDEquipmentComponent (Unequip)"));
    }

}

#undef LOCTEXT_NAMESPACE
