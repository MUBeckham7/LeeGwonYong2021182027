// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DDCharacterBase.generated.h"

UENUM()
enum class EcharacterControlType : uint8
{
	Shoulder,
	Quater
};

UCLASS()
class THEDOLDRUMS_API ADDCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADDCharacterBase();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class USkeletalMeshComponent> BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class USkeletalMeshComponent> FaceMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class USkeletalMeshComponent> FeetMesh;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//TObjectPtr<class USkeletalMeshComponent> LegsMesh;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//TObjectPtr<class USkeletalMeshComponent> TorsoMesh;

	UPROPERTY(VisibleAnywhere,BluePrintReadWrite)
	TObjectPtr<class UGroomBindingAsset> Beard;

protected:
	virtual void SetCharacterControlData(const class UDDCharacterControlData* CharacterControlData);

	UPROPERTY(EditAnywhere, Category = CharaterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<EcharacterControlType, class UDDCharacterControlData*> CharacterControlManager;
};
