// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DDCharacterBase.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "Interface/DDItemInteractionInterface.h"
#include "DDCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API ADDCharacterPlayer: public ADDCharacterBase , public IDDItemInteractionInterface
{
	GENERATED_BODY()

public:
	ADDCharacterPlayer();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//ĳ���� ��Ʈ�� ����

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	void SetCharacterControl(EcharacterControlType NewCharacterControlType);
	virtual void SetCharacterControlData(const class UDDCharacterControlData* CharacterControlData) override;


	//ī�޶� ����
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<class UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, Meta =(AllowPrivateAccess = "true"))
	TObjectPtr<class UCineCameraComponent> MovieCamera;

	//�Է� ����
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderRunAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess =  "true"))
	TObjectPtr<class UInputAction> ChangeControlAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> InterActionVal;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MouseWheelAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> UseItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> OpenInventoryAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> DropItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LeftMouseClickAction;


	void ShoulderMove(const FInputActionValue& Value);
	void ShoulderLook(const FInputActionValue& Value);
	void InterActionFun(const FInputActionValue& Value);
	void ShoudlerRun(const FInputActionValue& Value); 
	void ShoudlerWalk(const FInputActionValue& Value);
	void ChangeView(const FInputActionValue& Value);
	void OnBurnWheelStarted(const FInputActionInstance& Instance);
	void UseItem(const FInputActionValue& Value);
	void OpenInventory(const FInputActionValue& Value);
	void DropItem(const FInputActionInstance& Instance);
	void LeftMouseClick(const FInputActionInstance& Instance);

	EcharacterControlType CurrentCharacterControlType;

	float TargetWalkSpeed = 220.0f;
	float SpeedInterpSpeed = 5.0f;

public:	//ī�޶� ���� ���� �Լ� �� ����

	virtual void BumpPalmTreeChangeView() override;

	FRotator InitialControlRotation;

	// ����� ȸ�� ��
	FRotator BumpTreeTargetControlRotation;
	FRotator BornFireTargetControlRotation;

	uint32 bIsReturningToDefaultRotation : 1 ;
	uint32 bIsTurningToNewRotation : 1;
	uint32 bIsTurningToPersonalView : 1;


protected:	//ī�޶� ���� ���� �Լ�



protected:	//�ִϸ��̼� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> BumpTreeMontage;
	uint32 bBumpTree : 1;

	void ReturnToDefaultView();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Animation)
	TObjectPtr<class UAnimMontage> BornFireIdleMontage;
	uint32 bBornFire : 1;
	
	UPROPERTY()
	FVector TargetSocketOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> HighGrassScoopWaterMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> DrinkWaterMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> AxingMontage;

private:	// ���ǿ�� ����

	FTimerHandle WheelResetTimerHandle;


	UPROPERTY(EditAnywhere,Category = "InputWheel")
	float WheelResetDelay = 1.0f;



public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Animation)
	TObjectPtr<class UAnimMontage> WheelMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class UCameraShakeBase> BumpTreeCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UCameraShakeBase> AxingTreeCameraShake;

	int32 WheelCount = 0;

	void ResetWheelCount();

	void AxeAction();


//Inventory 
	protected:

		UPROPERTY()
		TSubclassOf<class UNarrativeItem> CurrentInventoryItemClass;
};
