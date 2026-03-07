// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DDEquipmentComponent.h"
#include "Components/SkeletalMeshComponent.h"

UDDEquipmentComponent::UDDEquipmentComponent()
{
}

void UDDEquipmentComponent::Initialize(TMap<EDDEquippableSlot, USkeletalMeshComponent*> ClothingMeshes, class USkeletalMeshComponent* InLeaderPoseComponent)
{
	LeaderPoseComponent = InLeaderPoseComponent;

	DDEquippableComponents = ClothingMeshes;

	for (auto& ClothingMeshKP : ClothingMeshes)
	{
		if (ClothingMeshKP.Value)
		{
			DefaultClothing.Add(ClothingMeshKP.Key, ClothingMeshKP.Value->GetSkeletalMeshAsset());
			DefaultClothingMaterials.Add(ClothingMeshKP.Key, FDefaultClothingMeshMaterialsDD(ClothingMeshKP.Value->GetMaterials()));
		}
	}

}

class UDDEquippableItem* UDDEquipmentComponent::GetEquippedItemAtSlot(const EDDEquippableSlot Slot)
{
	if (DDEquippedItems.Contains(Slot))
	{
		return *DDEquippedItems.Find(Slot);
	}
	else
	{
		return nullptr;
	}
}

float UDDEquipmentComponent::GetEquippedItemsWeight() const
{
	float TotalWeight = 0.f;

	for (auto& EquippedItemKP : DDEquippedItems)
	{
		if (EquippedItemKP.Value)
		{
			TotalWeight += EquippedItemKP.Value->Weight;
		}
	}

	return TotalWeight;
}

void UDDEquipmentComponent::DDEquipItem(class UDDEquippableItem* DDEquippable)
{
	if (DDEquippable)
	{
		//Remove the old item from our equipped items if one is already equipped
		if (DDEquippedItems.Contains(DDEquippable->DDEquippableSlot))
		{
			if (UDDEquippableItem* AlreadyEquippedItem = *DDEquippedItems.Find(DDEquippable->DDEquippableSlot))
			{
				AlreadyEquippedItem->SetActive(false);
			}
		}

		DDEquippedItems.Add(DDEquippable->DDEquippableSlot, DDEquippable);

		DDEquippable->HandleEquip();

		OnItemDDEquipped.Broadcast(DDEquippable->DDEquippableSlot, DDEquippable);
	}
}

void UDDEquipmentComponent::DDUnequipItem(class UDDEquippableItem* DDEquippable)
{
	if (DDEquippable)
	{
		DDEquippedItems.Remove(DDEquippable->DDEquippableSlot);

		DDEquippable->HandleUnequip();

		OnItemDDUnEquipped.Broadcast(DDEquippable->DDEquippableSlot, DDEquippable);
	}
}