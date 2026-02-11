// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquippableItem.h"
#include "DDEquippableItem_Backpack.generated.h"

UENUM(BlueprintType)
enum class EDDEquippableSlot : uint8
{
	ES_Torso UMETA(DisplayName = "Torso"),
	ES_Legs UMETA(DisplayName = "Legs"),
	ES_Feet UMETA(DisplayName = "Feet"),
	ES_Helmet UMETA(DisplayName = "Helmet"),
	ES_Hands UMETA(DisplayName = "Hands"),
	ES_Backpack UMETA(DisplayName = "Backpack"),
	ES_Necklace UMETA(DisplayName = "Necklace"),
	ES_Holster UMETA(DisplayName = "Holster"),
	ES_Weapon UMETA(DisplayName = "Weapon"),
	ES_Custom1 UMETA(DisplayName = "Custom1"),
	ES_Custom2 UMETA(DisplayName = "Custom2"),
	ES_Custom3 UMETA(DisplayName = "Custom3"),
	ES_Custom4 UMETA(DisplayName = "Custom4"),
	ES_Custom5 UMETA(DisplayName = "Custom5"),
};

/**
 * The base class for an equippable item the player can put on. Networking is built right in.
 */
UCLASS()
class THEDOLDRUMS_API UDDEquippableItem : public UNarrativeItem
{
	GENERATED_BODY()

protected:

	friend class UDDEquipmentComponent;

	UDDEquippableItem();

	/**Allows you to override what equipping the item does. By default this sets the players mesh to the Equippable Mesh, but perhaps
	you want a weapon actor to spawn in, or have an equippable aura effect that follows the player. by overriding HandleEquip you can
	do whatever custom logic you want. */
	UFUNCTION(BlueprintNativeEvent, Category = "Equippable")
	void HandleEquip();
	virtual void HandleEquip_Implementation();

	/**Allows you to override what happens when the item unequips. */
	UFUNCTION(BlueprintNativeEvent, Category = "Equippable")
	void HandleUnequip();
	virtual void HandleUnequip_Implementation();

	virtual void Activated_Implementation() override;
	virtual void Deactivated_Implementation() override;

	/**The slot this item equips to*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equippable")
	EDDEquippableSlot DDEquippableSlot;

};
/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API UDDEquippableItem_Backpack : public UDDEquippableItem
{
	GENERATED_BODY()
	

protected:
	UDDEquippableItem_Backpack();

	virtual void HandleEquip_Implementation() override;
	virtual void HandleUnequip_Implementation() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equippable")
	class USkeletalMesh* ClothingMesh1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equippable")
	class USkeletalMesh* ClothingMesh2;

	UPROPERTY(Transient)
	USkeletalMeshComponent* ClothingMesh2Component = nullptr;

	/**Should this item set the leader pose component?*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equippable")
	bool bShouldSetLeaderPose;


	/**The materials to apply to the clothing mesh*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equippable")
	TArray<class UMaterialInterface*> ClothingMaterials;


};
