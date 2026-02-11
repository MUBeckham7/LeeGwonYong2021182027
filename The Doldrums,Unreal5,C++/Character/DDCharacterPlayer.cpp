// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DDCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "CineCameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "Interface/DDCharacterInterface.h"
#include "EnhancedInputSubsystems.h"
#include "DDCharacterControlData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include <Prop/DDPalmTree.h>
#include <Prop/DDTent.h>
#include <Item/DDItemBranch.h>
#include <Item/DDEquipClothTShirt.h>
#include <Item/DDEquipClothPants.h>
#include <Item/DDEquipClothWatch.h>
#include <Item/DDEquipClothBag.h>
#include <Item/DDItemWaterBottle.h>
#include <Item/DDItemAxe.h>
#include <Prop/DDGrassOne.h>
#include <Prop/DDGeneratedDynamicMeshActorLog.h>
#include <Item/DDGeneratedDynamicMeshFlint.h>
#include "Animation/DDAnimInstance.h"
#include "TimerManager.h"
#include "Components/WidgetComponent.h"
#include "Player/DDPlayerController.h"
#include "Item/DDEquipmentItemData.h"
#include "State/DDPlayerState.h"
#include "NarrativeItem.h"

ADDCharacterPlayer::ADDCharacterPlayer()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bUsePawnControlRotation = false;

	//FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//FollowCamera->bUsePawnControlRotation = false;
	CameraBoom->SocketOffset = FVector(300.0f, 0.0f, 75.0f);
	CameraBoom->TargetOffset = FVector(0.0f, -8.0f, 0.0f);

	MovieCamera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("MovieCam"));
	MovieCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);



	MovieCamera->bUsePawnControlRotation = false;

	CameraBoom->bDoCollisionTest = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);



	static ConstructorHelpers::FObjectFinder<UInputAction> ShoulderRunActionControlRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_ShoulderRun.IA_ShoulderRun'"));
	if (nullptr != ShoulderRunActionControlRef.Object)
	{
		ShoulderRunAction = ShoulderRunActionControlRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputChangeActionControlRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_ChangeControl.IA_ChangeControl'"));
	if (nullptr != InputChangeActionControlRef.Object)
	{
		ChangeControlAction = InputChangeActionControlRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShoulderMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_ShoulderMove.IA_ShoulderMove'"));
	if (nullptr != InputActionShoulderMoveRef.Object)
	{
		ShoulderMoveAction = InputActionShoulderMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShoulderLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_ShoulderLook.IA_ShoulderLook'"));
	if (nullptr != InputActionShoulderLookRef.Object)
	{
		ShoulderLookAction = InputActionShoulderLookRef.Object;
	}


	static ConstructorHelpers::FObjectFinder<UInputAction> InputInterActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Interaction.IA_Interaction'"));
	if (nullptr != InputInterActionRef.Object)
	{
		InterActionVal = InputInterActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMouseWheel(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_MouseWheel.IA_MouseWheel'"));
	if (nullptr != InputActionMouseWheel.Object)
	{
		MouseWheelAction = InputActionMouseWheel.Object;


	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputUseItemActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_UseItem.IA_UseItem'"));
	if (nullptr != InputUseItemActionRef.Object)
	{
		UseItemAction = InputUseItemActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> OpenInventoryActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Inventory.IA_Inventory'"));
	if (nullptr != OpenInventoryActionRef.Object)
	{
		OpenInventoryAction = OpenInventoryActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> DropItemActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_DropItem.IA_DropItem'"));
	if (nullptr != DropItemActionRef.Object)
	{
		DropItemAction = DropItemActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LeftMouseClickActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_LeftMouseClick.IA_LeftMouseClick'"));
	if (nullptr != LeftMouseClickActionRef.Object)
	{
		LeftMouseClickAction = LeftMouseClickActionRef.Object;
	}

	CurrentCharacterControlType = EcharacterControlType::Shoulder;

}

void ADDCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(ShoulderRunAction, ETriggerEvent::Triggered, this, &ADDCharacterPlayer::ShoudlerRun);
	EnhancedInputComponent->BindAction(ShoulderRunAction, ETriggerEvent::Completed, this, &ADDCharacterPlayer::ShoudlerWalk);
	EnhancedInputComponent->BindAction(ShoulderMoveAction, ETriggerEvent::Triggered, this, &ADDCharacterPlayer::ShoulderMove);
	EnhancedInputComponent->BindAction(ShoulderLookAction, ETriggerEvent::Triggered, this, &ADDCharacterPlayer::ShoulderLook);
	EnhancedInputComponent->BindAction(InterActionVal, ETriggerEvent::Triggered, this, &ADDCharacterPlayer::InterActionFun);
	EnhancedInputComponent->BindAction(MouseWheelAction, ETriggerEvent::Triggered, this, &ADDCharacterPlayer::OnBurnWheelStarted);
	EnhancedInputComponent->BindAction(ChangeControlAction, ETriggerEvent::Triggered, this, &ADDCharacterPlayer::ChangeView);
	EnhancedInputComponent->BindAction(UseItemAction, ETriggerEvent::Triggered, this, &ADDCharacterPlayer::UseItem);
	EnhancedInputComponent->BindAction(OpenInventoryAction, ETriggerEvent::Triggered, this, &ADDCharacterPlayer::OpenInventory);
	EnhancedInputComponent->BindAction(DropItemAction, ETriggerEvent::Triggered, this, &ADDCharacterPlayer::DropItem);
	EnhancedInputComponent->BindAction(LeftMouseClickAction, ETriggerEvent::Triggered, this, &ADDCharacterPlayer::LeftMouseClick);
}

void ADDCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	SetCharacterControl(CurrentCharacterControlType);


	InitialControlRotation = Controller->GetControlRotation();



}

void ADDCharacterPlayer::Tick(float DeltaSeconds)
{
	if (bIsReturningToDefaultRotation)	// 캐릭터의 등뒤로 돌아가는 카메라 무빙
	{			
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		FRotator CurrentRotation = Controller->GetControlRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, InitialControlRotation, DeltaSeconds, 7.0f); // 5.0f는 회전 속도

		Controller->SetControlRotation(NewRotation);
		Controller->SetIgnoreLookInput(true);

		// 거의 다 도달하면 종료
		if (NewRotation.Equals(InitialControlRotation, 0.1f))
		{
			bIsReturningToDefaultRotation = false;
			Controller->SetControlRotation(InitialControlRotation); // 보정
			//APlayerController
			Controller->ResetIgnoreLookInput();
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			if (bBumpTree)															//트리에 부딪히는 경우에만 몽타주 재생
			{
				bIsTurningToNewRotation = true;
				bBumpTree = false;

				const FVector CurrentForwardVector = GetActorForwardVector();

				BumpTreeTargetControlRotation = CurrentForwardVector.Rotation();

				BumpTreeTargetControlRotation.Pitch += 30.0f;
				BumpTreeTargetControlRotation.Yaw -= 20.0f;

			}
			else if (bBornFire)														//
			{
				bBornFire = false;

				const FVector CharacterForwardDirection = GetActorForwardVector();
				const FVector CharacterRightDirection = GetActorRightVector();

				FRotator ForwardRot = CharacterForwardDirection.Rotation();

				ForwardRot.Yaw += 210.0f;
				ForwardRot.Pitch -= -20.0f;

				BornFireTargetControlRotation = ForwardRot;

				TargetSocketOffset = FVector(250.0f, 0.0f, -40.0f);

				bIsTurningToPersonalView = true;
			}
			
		}
	}

	if (bIsTurningToNewRotation)		//나무에 부딪히는 뷰로 돌아가는 카메라 무빙
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		FRotator CurrentRotation = Controller->GetControlRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, BumpTreeTargetControlRotation, DeltaSeconds, 2.0f);

		Controller->SetControlRotation(NewRotation);
		Controller->SetIgnoreLookInput(true);
		if (NewRotation.Equals(BumpTreeTargetControlRotation, 0.1f))
		{
			//Controller->ResetIgnoreLookInput();
			Controller->SetControlRotation(BumpTreeTargetControlRotation);

			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();	//나무에 부딪히는 몽타주 재생
			AnimInstance->Montage_Play(BumpTreeMontage);
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			bIsTurningToNewRotation = false;
			//ReturnToDefaultView();
		}
	}

	if (bIsTurningToPersonalView)			//불 피울 때 아래로 가는 카메라 무빙
	{
		FRotator CurrentRotator = Controller->GetControlRotation();
		FRotator LerpedRotator = FMath::RInterpTo(CurrentRotator, BornFireTargetControlRotation, DeltaSeconds, 2.0f);
		Controller->SetControlRotation(LerpedRotator);
		Controller->SetIgnoreLookInput(true);


		FVector CurrentOffset = CameraBoom->SocketOffset;
		FVector LerpedOffset = FMath::VInterpTo(CurrentOffset, TargetSocketOffset, DeltaSeconds, 5.0f);
		CameraBoom->SocketOffset = LerpedOffset;

		bool bRotDone = LerpedRotator.Equals(BornFireTargetControlRotation, 0.1f);
		bool bOffsetDone = LerpedOffset.Equals(TargetSocketOffset, 1.0f);


		if (bRotDone && bOffsetDone)
		{
			Controller->SetControlRotation(BornFireTargetControlRotation);
			Controller->ResetIgnoreLookInput();
			CameraBoom->SocketOffset = TargetSocketOffset;

			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			AnimInstance->Montage_Play(BornFireIdleMontage);

			bIsTurningToPersonalView = false;
		}
	}


	float CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;
	float NewSpeed = FMath::FInterpTo(CurrentSpeed, TargetWalkSpeed, DeltaSeconds, SpeedInterpSpeed);
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void ADDCharacterPlayer::SetCharacterControl(EcharacterControlType NewCharacterControlType)
{
	UDDCharacterControlData* NewCharacterControl = CharacterControlManager[NewCharacterControlType];
	check(NewCharacterControl);

	SetCharacterControlData(NewCharacterControl);

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		UInputMappingContext* NewMappingContext = NewCharacterControl->InputMappingContext;
		if (NewMappingContext)
		{
			Subsystem->AddMappingContext(NewMappingContext, 0);
		}
	}

	CurrentCharacterControlType = NewCharacterControlType;
}

void ADDCharacterPlayer::SetCharacterControlData(const UDDCharacterControlData* CharacterControlData)
{
	Super::SetCharacterControlData(CharacterControlData);

	CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
	CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotaion);
	CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
	CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
	CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;
	CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;

}

void ADDCharacterPlayer::ShoulderMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);

	if (UDDAnimInstance* AnimInstance = Cast<UDDAnimInstance>(BodyMesh->GetAnimInstance()))
	{
		if (AnimInstance->Montage_IsPlaying(BornFireIdleMontage))
			AnimInstance->Montage_Stop(0.2f, BornFireIdleMontage);

		CameraBoom->SocketOffset = FVector(300.0f, 0.0f, 75.0f);
		CameraBoom->TargetOffset = FVector(0.0f, -8.0f, 0.0f);
	}
}

void ADDCharacterPlayer::ShoulderLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}


void ADDCharacterPlayer::ChangeView(const FInputActionValue& Value)
{
	

	//CameraBoom->TargetArmLength = 400.0f;

	//Controller->SetControlRotation(ForwardRot);

}

void ADDCharacterPlayer::InterActionFun(const FInputActionValue& Value)
{
	TArray<AActor*> Result;
	GetOverlappingActors(Result, AActor::StaticClass());

		for (auto TmpActor : Result)
		{

			if (TmpActor->IsA(ADDEquipClothPants::StaticClass()))
			{
				ADDEquipClothPants* Pants = Cast<ADDEquipClothPants>(TmpActor);
				Pants->OnInteract();
			}
			else if (TmpActor->IsA(ADDPalmTree::StaticClass()))
			{
				ADDPalmTree* Palm = Cast<ADDPalmTree>(TmpActor);
				Palm->OnInteract();
			}
			else if (TmpActor->IsA(ADDTent::StaticClass()))
			{
				ADDTent* Tent = Cast<ADDTent>(TmpActor);
				Tent->OnInteract();
			}
			else if (TmpActor->IsA(ADDItemBranch::StaticClass()))
			{
				ADDItemBranch* Branch = Cast<ADDItemBranch>(TmpActor);
				Branch->OnInteract();

				if (UDDAnimInstance* AnimInstance = Cast<UDDAnimInstance>(BodyMesh->GetAnimInstance()))
				{
					AnimInstance->bGrabbedBranch = true;
				}
				
				CurrentInventoryItemClass = Branch->ItemDDBranchClass;

			}
			else if (ADDGeneratedDynamicMeshFlint* Flint = Cast<ADDGeneratedDynamicMeshFlint>(TmpActor))
			{
				if (UDDAnimInstance* AnimInstance = Cast<UDDAnimInstance>(BodyMesh->GetAnimInstance()))
				{
					if (AnimInstance->bGrabbedBranch)
					{
						bBornFire = true;

						ReturnToDefaultView();
					}
				}
			}
			else if (ADDGeneratedDynamicMeshActorLog* Log = Cast<ADDGeneratedDynamicMeshActorLog>(TmpActor))
			{

			}
			else if (TmpActor->IsA(ADDItemWaterBottle::StaticClass()))
			{
				ADDItemWaterBottle* WaterBottle = Cast<ADDItemWaterBottle>(TmpActor);
				WaterBottle->OnInteract();

				/*if (UDDAnimInstance* AnimInstance = Cast<UDDAnimInstance>(BodyMesh->GetAnimInstance()))
				{
					AnimInstance->Montage_Play(HighGrassScoopWaterMontage);
				}*/
				CurrentInventoryItemClass = WaterBottle->ItemDDWaterBottleClass;
			}
			else if (TmpActor->IsA(ADDGrassOne::StaticClass()))
			{
				ADDGrassOne* Grass = Cast<ADDGrassOne>(TmpActor);
				if (EquipmentNow == EItemType::WaterBottle)
				{
					if (UDDAnimInstance* AnimInstance = Cast<UDDAnimInstance>(BodyMesh->GetAnimInstance()))
					{
						AnimInstance->Montage_Play(HighGrassScoopWaterMontage);
					}
				}
			}
			else if (TmpActor->IsA(ADDEquipClothTShirt::StaticClass()))
			{
				ADDEquipClothTShirt* TShirt = Cast<ADDEquipClothTShirt>(TmpActor);
				TShirt->OnInteract();
			}
			else if (TmpActor->IsA(ADDEquipClothWatch::StaticClass()))
			{
				ADDEquipClothWatch* Watch = Cast<ADDEquipClothWatch>(TmpActor);
				Watch->OnInteract();
			}
			else if (TmpActor->IsA(ADDEquipClothBag::StaticClass()))
			{
				ADDEquipClothBag* Bag = Cast<ADDEquipClothBag>(TmpActor);
				Bag->OnInteract();
			}
			else if (TmpActor->IsA(ADDItemAxe::StaticClass()))
			{
				ADDItemAxe* Axe = Cast<ADDItemAxe>(TmpActor);
				Axe->OnInteract();
			}

		}
}


void ADDCharacterPlayer::ShoudlerRun(const FInputActionValue& Value)
{

	TargetWalkSpeed = 480.0f;

}

void ADDCharacterPlayer::ShoudlerWalk(const FInputActionValue& Value)
{
	TargetWalkSpeed = 220.0f;

}



void ADDCharacterPlayer::OnBurnWheelStarted(const FInputActionInstance& Instance)
{

	if (!Instance.GetValue().Get<bool>())
		return;

	WheelCount++;

	if (UDDAnimInstance* AnimInstance = Cast<UDDAnimInstance>(BodyMesh->GetAnimInstance()))
	{
		if (AnimInstance->Montage_IsPlaying(BornFireIdleMontage))
		{

			AnimInstance->Montage_Play(WheelMontage);

			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		}


	}



	GetWorldTimerManager().ClearTimer(WheelResetTimerHandle);

	GetWorldTimerManager().SetTimer(WheelResetTimerHandle, this, &ADDCharacterPlayer::ResetWheelCount, WheelResetDelay, false);

}

void ADDCharacterPlayer::UseItem(const FInputActionValue& Value)
{


	switch (EquipmentNow)
	{
	case EItemType::WaterBottle:

		if (UDDAnimInstance* AnimInstance = Cast<UDDAnimInstance>(BodyMesh->GetAnimInstance()))
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

			AnimInstance->Montage_Play(DrinkWaterMontage);
		}
		break;
	case EItemType::Axe:

		if (UDDAnimInstance* AnimInstance = Cast<UDDAnimInstance>(BodyMesh->GetAnimInstance()))
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

			AnimInstance->Montage_Play(AxingMontage);

			
		}
		break;


	}
}

void ADDCharacterPlayer::OpenInventory(const FInputActionValue& Value)
{
	//InventoryWidget->SetVisibility(ESlateVisibility::Visible);


}

void ADDCharacterPlayer::DropItem(const FInputActionInstance& Instance)
{



	switch (EquipmentNow)
	{
	case EItemType::Branch:
		if (EquipmentBranch)
		{
			UWorld* World = GetWorld();
			if (!World) return;

			FName SocketName = TEXT("hand_rBranchSocket");
			FVector SpawnLocation = GetMesh()->GetSocketLocation(SocketName) + GetActorForwardVector();
			FRotator SpawnRotation = GetMesh()->GetSocketRotation(SocketName);

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			UDDEquipmentItemData* EquipData = Cast<UDDEquipmentItemData>(CurrentEquippedItem);
			if (EquipData && EquipData->ItemActorClass)
			{
				AActor* DroppedActor = World->SpawnActor<AActor>(EquipData->ItemActorClass, SpawnLocation, SpawnRotation, SpawnParams);
				if (DroppedActor)
				{
					UStaticMeshComponent* MeshComp = DroppedActor->FindComponentByClass<UStaticMeshComponent>();
					if (MeshComp)
					{
						MeshComp->SetSimulatePhysics(true);
						MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
						FVector ThrowDir = GetActorForwardVector();
						MeshComp->AddImpulse(ThrowDir * 10.0f, NAME_None, true);
					}
				}

				ADDPlayerState* MyPs = GetPlayerState<ADDPlayerState>();
				if (MyPs && MyPs->Inventory)
				{
					if (CurrentInventoryItemClass) {
						TSoftClassPtr<UNarrativeItem>SoftPtr(CurrentInventoryItemClass);

						UNarrativeItem* ItemInstance = MyPs->Inventory->FindItemByClass(SoftPtr);
						if (ItemInstance)
						{
							MyPs->Inventory->RemoveItem(ItemInstance);
						}
					}
				}

			}
			EquipmentBranch->SetStaticMesh(nullptr);

			// 인벤토리/상태 초기화
			CurrentEquippedItem = nullptr;
		}
		break;
	case EItemType::WaterBottle:
		if (EquipmentWaterBottle)
		{
			UWorld* World = GetWorld();
			if (!World) return;

			FName SocketName = TEXT("hand_rWaterBottleSocket");
			FVector SpawnLocation = GetMesh()->GetSocketLocation(SocketName) + GetActorForwardVector();
			FRotator SpawnRotation = GetMesh()->GetSocketRotation(SocketName);
			SpawnRotation.Yaw += 180.0f;

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			UDDEquipmentItemData* EquipData = Cast<UDDEquipmentItemData>(CurrentEquippedItem);
			if (EquipData && EquipData->ItemActorClass)
			{
				AActor* DroppedActor = World->SpawnActor<AActor>(EquipData->ItemActorClass, SpawnLocation, SpawnRotation, SpawnParams);
				if (DroppedActor)
				{
					UStaticMeshComponent* MeshComp = DroppedActor->FindComponentByClass<UStaticMeshComponent>();
					if (MeshComp)
					{
						MeshComp->SetSimulatePhysics(true);
						MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
						FVector ThrowDir = GetActorForwardVector();
						MeshComp->AddImpulse(ThrowDir * 20.0f, NAME_None, true);
					}
				}

				ADDPlayerState* MyPs = GetPlayerState<ADDPlayerState>();
				if (MyPs && MyPs->Inventory)
				{
					if (CurrentInventoryItemClass) {
						TSoftClassPtr<UNarrativeItem>SoftPtr(CurrentInventoryItemClass);

						UNarrativeItem* ItemInstance = MyPs->Inventory->FindItemByClass(SoftPtr);
						if (ItemInstance)
						{
							MyPs->Inventory->RemoveItem(ItemInstance);
						}
					}
				}


			}
			EquipmentWaterBottle->SetStaticMesh(nullptr);

			// 인벤토리/상태 초기화
			CurrentEquippedItem = nullptr;
		}
		break;
	case EItemType::Axe:
		if (EquipmentAxe)
		{
			UWorld* World = GetWorld();
			if (!World) return;

			FName SocketName = TEXT("hand_rAxeSocket");
			FVector SpawnLocation = GetMesh()->GetSocketLocation(SocketName) + GetActorForwardVector();
			FRotator SpawnRotation = GetMesh()->GetSocketRotation(SocketName);
			SpawnRotation.Yaw += 180.0f;

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			UDDEquipmentItemData* EquipData = Cast<UDDEquipmentItemData>(CurrentEquippedItem);
			if (EquipData && EquipData->ItemActorClass)
			{
				AActor* DroppedActor = World->SpawnActor<AActor>(EquipData->ItemActorClass, SpawnLocation, SpawnRotation, SpawnParams);
				if (DroppedActor)
				{
					UStaticMeshComponent* MeshComp = DroppedActor->FindComponentByClass<UStaticMeshComponent>();
					if (MeshComp)
					{
						MeshComp->SetSimulatePhysics(true);
						MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
						FVector ThrowDir = GetActorForwardVector();
						MeshComp->AddImpulse(ThrowDir * 20.0f, NAME_None, true);
					}
				}

				ADDPlayerState* MyPs = GetPlayerState<ADDPlayerState>();
				if (MyPs && MyPs->Inventory)
				{
					if (CurrentInventoryItemClass) {
						TSoftClassPtr<UNarrativeItem>SoftPtr(CurrentInventoryItemClass);

						UNarrativeItem* ItemInstance = MyPs->Inventory->FindItemByClass(SoftPtr);
						if (ItemInstance)
						{
							MyPs->Inventory->RemoveItem(ItemInstance);
						}
					}
				}


			}
			EquipmentAxe->SetStaticMesh(nullptr);

			// 인벤토리/상태 초기화
			CurrentEquippedItem = nullptr;
		}
		break;

	}



}

void ADDCharacterPlayer::LeftMouseClick(const FInputActionInstance& Instance)
{
	UE_LOG(LogTemp, Warning, TEXT("LeftMouseClick"));
}


void ADDCharacterPlayer::ResetWheelCount()
{
	WheelCount = 0;
	UE_LOG(LogTemp, Warning, TEXT("WheelCount = %d"), WheelCount);

	if (UDDAnimInstance* AnimInstance = Cast<UDDAnimInstance>(BodyMesh->GetAnimInstance()))
	{
		if (AnimInstance->Montage_IsPlaying(WheelMontage))
		{

			AnimInstance->Montage_Stop(0.2f, WheelMontage);

			TArray<AActor*> Result;
			GetOverlappingActors(Result, AActor::StaticClass());
			for (auto TmpActor : Result)
			{
				UE_LOG(LogTemp, Warning, TEXT("FuckNotifty"));
				if (ADDGeneratedDynamicMeshFlint* Log = Cast<ADDGeneratedDynamicMeshFlint>(TmpActor))
				{
					UE_LOG(LogTemp, Warning, TEXT("Fuck3"));
					Log->DynamicMeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
					Log->DynamicMeshComp->SetNotifyRigidBodyCollision(true);
					Log->DynamicMeshComp->SetGenerateOverlapEvents(true);

					Log->SubtractWithTool(EquipmentBranch, EquipmentBranch->GetComponentLocation());

					GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
				}
			}

			EquipmentBranch->SetSimulatePhysics(true);
			EquipmentBranch->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			//Equipment->SetStaticMesh(nullptr);
		}

	}
}

void ADDCharacterPlayer::AxeAction()
{
	if (UDDAnimInstance* AnimInstance = Cast<UDDAnimInstance>(BodyMesh->GetAnimInstance()))
	{
		if (AnimInstance->Montage_IsPlaying(AxingMontage))
		{

			TArray<AActor*> Result;
			GetOverlappingActors(Result, AActor::StaticClass());
			for (auto TmpActor : Result)
			{
				UE_LOG(LogTemp, Warning, TEXT("FuckNotifty"));
				if (ADDGeneratedDynamicMeshActorLog* Log = Cast<ADDGeneratedDynamicMeshActorLog>(TmpActor))
				{
					UE_LOG(LogTemp, Warning, TEXT("Fuck3"));
					Log->DynamicMeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
					Log->DynamicMeshComp->SetNotifyRigidBodyCollision(true);
					Log->DynamicMeshComp->SetGenerateOverlapEvents(true);

					Log->SubtractWithTool(EquipmentAxe, EquipmentAxe->GetComponentLocation());


					GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
				}
			}

		}
	}

}


void ADDCharacterPlayer::BumpPalmTreeChangeView()
{
	BumpTreeTargetControlRotation = InitialControlRotation;

	bBumpTree = true;

	ReturnToDefaultView();
}

void ADDCharacterPlayer::ReturnToDefaultView()
{
	 // <- BeginPlay에서 저장해둔 초기값
	bIsReturningToDefaultRotation = true;
}



