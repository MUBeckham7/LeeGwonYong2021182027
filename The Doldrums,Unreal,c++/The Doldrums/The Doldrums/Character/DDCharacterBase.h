// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/DDCharacterItemInterface.h"
#include "Item/DDItemDataAsset.h"
#include "Interface/DDCharacterWidgetInterface.h"
#include "DDCharacterBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDDCharacter, Log, All);

UENUM()
enum class EcharacterControlType : uint8
{
	Shoulder,
	Quater
};

DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, class UDDItemDataAsset* InItemData);
USTRUCT(BlueprintType)
struct FTakeItemDelegateWrapper
{
	GENERATED_BODY()
	FTakeItemDelegateWrapper() {}
	FTakeItemDelegateWrapper(const FOnTakeItemDelegate& InItemDelegate) : ItemDelegate(InItemDelegate){}

	FOnTakeItemDelegate ItemDelegate;
};

UCLASS()
class THEDOLDRUMS_API ADDCharacterBase : public ACharacter , public IDDCharacterItemInterface , public IDDCharacterWidgetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADDCharacterBase();

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class USkeletalMeshComponent> BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class USkeletalMeshComponent> FaceMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class USkeletalMeshComponent> FeetMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class USkeletalMeshComponent> WatchMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class USkeletalMeshComponent> BagMeshPart1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class USkeletalMeshComponent> BagMeshPart2;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//TObjectPtr<class USkeletalMeshComponent> LegsMesh;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//TObjectPtr<class USkeletalMeshComponent> Torso;


protected:
	virtual void SetCharacterControlData(const class UDDCharacterControlData* CharacterControlData);

	UPROPERTY(EditAnywhere, Category = CharaterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<EcharacterControlType, class UDDCharacterControlData*> CharacterControlManager;

//ItemSection
protected:

	UPROPERTY()
	TArray<FTakeItemDelegateWrapper> TakeItemActions;

	virtual void TakeItem(class UDDItemDataAsset* InItemData) override;
	virtual void EquipBranch(class UDDItemDataAsset* InItemData);
	virtual void EquipWaterBottle(class UDDItemDataAsset* InItemData);
	virtual void EatFood(class UDDItemDataAsset* InItemData);
	virtual void EquipClothTShirt(class UDDItemDataAsset* InItemData);
	virtual void EquipClothPants(class UDDItemDataAsset* InItemData);
	virtual void EquipClothWatch(class UDDItemDataAsset* InItemData);
	virtual void EquipClothBag(class UDDItemDataAsset* InItemData);
	virtual void EquipAxe(class UDDItemDataAsset* InItemData);
	virtual void EquipTorch(class UDDItemDataAsset* InItemData);
	virtual void EquipMachete(class UDDItemDataAsset* InItemData);
	virtual void EquipPalm(class UDDItemDataAsset* InItemData);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Equipment)
	EItemType EquipmentNow;

	UPROPERTY()
	UDDItemDataAsset* CurrentEquippedItem;

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Equipment,Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> EquipmentBranch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> EquipmentWaterBottle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> EquipmentTShirt;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> EquipmentPants;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> EquipmentWatch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> EquipmentBagTie;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> EquipmentBagBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> EquipmentAxe;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> EquipmentTorchBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> EquipmentTorchPartC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> EquipmentTorchPartL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> EquipmentMachete;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> EquipmentFoodPalm;

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDDCharacterStatComponent> Stat;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDDWidgetComponent> HungerStat;

	TSubclassOf<UUserWidget> CharacterStatWidgetClass;

	UUserWidget* CharacterStatWidget;

	virtual void SetupHungerCharacterWidget(class UDDUserWidget* InUserWidget) override;
	virtual void SetupThirstCharacterWidget(class UDDUserWidget* InUserWidget) override;



public:
	void SetDead();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	bool bIsInDesiredTimeRange = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Time")
	float UDSTime = 0;

	UPROPERTY(BlueprintReadWrite,Category = "Item")
	TSubclassOf<AActor> DroppedItemC;

protected:
	UFUNCTION(BlueprintCallable, Category = "Drop|Equipment")
	void DropItemAndClearEquippedMesh(const AActor* DI);

	UFUNCTION(BlueprintCallable,Category = "Inventory|Use")
	void DistinguishItem(class UNarrativeItem* Item);

	UFUNCTION()
	void ResolveItemTypeFromNarrativeItem(const UNarrativeItem* Item);


};
