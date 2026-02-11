// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/DDEquippableItem_Backpack.h"
#include "DDEquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemDDEquipped, const EDDEquippableSlot, Slot, class UDDEquippableItem*, DDEquipable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemDDUnEquipped, const EDDEquippableSlot, Slot, class UDDEquippableItem*, DDEquipable);

USTRUCT()
struct FDefaultClothingMeshMaterialsDD
{

	GENERATED_BODY()

	FDefaultClothingMeshMaterialsDD() {};
	FDefaultClothingMeshMaterialsDD(TArray<class UMaterialInterface*> InMaterials) : DDMaterials(InMaterials) {};

	UPROPERTY()
	TArray<class UMaterialInterface*> DDMaterials;
};

/**
 * 
 */
UCLASS(ClassGroup = (Narrative), DisplayName = "Narrative Equipment", meta = (BlueprintSpawnableComponent))
class THEDOLDRUMS_API UDDEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class UDDEquippableItem;
	friend class UDDEquippableItem_Backpack;


public:
	UDDEquipmentComponent();

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	virtual void Initialize(TMap<EDDEquippableSlot, USkeletalMeshComponent*> ClothingMeshes, class USkeletalMeshComponent* LeaderPoseComponent);

	//Return the item equipped at the given slot
	UFUNCTION(BlueprintPure, Category = "Equipment")
	class UDDEquippableItem* GetEquippedItemAtSlot(const EDDEquippableSlot Slot);

	//Return how much all of our equipped items weigh
	UFUNCTION(BlueprintPure, Category = "Equipment")
	virtual float GetEquippedItemsWeight() const;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnItemDDEquipped OnItemDDEquipped;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnItemDDUnEquipped OnItemDDUnEquipped;

protected:

	//Mark the item as equipped/unequipped
	virtual void DDEquipItem(class UDDEquippableItem* DDEquippable);
	virtual void DDUnequipItem(class UDDEquippableItem* DDEquippable);

	/**When we put a new item on, we need to tell it to follow the leader pose component, so we store that here. */
	UPROPERTY()
	class USkeletalMeshComponent* LeaderPoseComponent;

	/**We cache this so when an item is removed we can set it back to the default*/
	UPROPERTY()
	TMap<EDDEquippableSlot, USkeletalMesh*> DefaultClothing;

	/**We cache this so when an item is removed we can set it back to the default materials*/
	UPROPERTY()
	TMap<EDDEquippableSlot, FDefaultClothingMeshMaterialsDD> DefaultClothingMaterials;

	/**The skeletal meshes we'll be changing if a player equips an item*/
	UPROPERTY()
	TMap<EDDEquippableSlot, USkeletalMeshComponent*> DDEquippableComponents;

	/**All of the items that are currently equipped are stored in here*/
	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	TMap<EDDEquippableSlot, UDDEquippableItem*> DDEquippedItems;


public:

	FORCEINLINE class USkeletalMeshComponent* GetLeaderPoseComponent() const { return LeaderPoseComponent; };
	FORCEINLINE TMap<EDDEquippableSlot, USkeletalMeshComponent*> GetEquippableComponents() const { return DDEquippableComponents; };
	FORCEINLINE TMap<EDDEquippableSlot, USkeletalMesh*> GetDefaultClothing() const { return DefaultClothing; };


	
};
