// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DDCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMesh.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DDCharacterControlData.h"
#include "Item/DDEquipmentItemData.h"
#include "Components/WidgetComponent.h"
#include "UI/DDWidgetComponent.h"
#include "UI/DDUserWidget.h"
#include "CharacterComponent/DDCharacterStatComponent.h"
#include "UI/DDStateWidget.h"
#include "Animation/DDAnimInstance.h"
#include "Niagara/DDFireActor.h"
#include "NarrativeItem.h"

DEFINE_LOG_CATEGORY(LogDDCharacter);


// Sets default values
ADDCharacterBase::ADDCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true ;
	//Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 520.0f;
	GetCharacterMovement()->AirControl = 0.7f;
	GetCharacterMovement()->MaxWalkSpeed = 220.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1500.0f;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

	//static ConstructorHelpers::FClassFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	//if (CharacterMeshRef.Class)
	//{
	//	
	//}


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterBodyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/MetaHumans/Nasim/Body/m_med_nrw_body.m_med_nrw_body'"));
	if (CharacterBodyMeshRef.Object)
	{
		BodyMesh = GetMesh();
		GetMesh()->SetSkeletalMesh(CharacterBodyMeshRef.Object);

	}


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterFaceMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/MetaHumans/Nasim/Face/Nasim_FaceMesh.Nasim_FaceMesh'"));
	if (CharacterFaceMeshRef.Object)
	{

		FaceMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FaceMesh"));
		FaceMesh->SetSkeletalMesh(CharacterFaceMeshRef.Object);
		FaceMesh->SetupAttachment(BodyMesh);

		FaceMesh->SetLeaderPoseComponent(BodyMesh);
		FaceMesh->SetRelativeLocation(FVector3d(0.0f, 0.0f, -0.04f));
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterFeetMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/MetaHumans/Common/Male/Medium/NormalWeight/Shoes/CasualSneakers/m_med_nrw_shs_casualsneakers_Cinematic.m_med_nrw_shs_casualsneakers_Cinematic'"));
	if (CharacterFeetMeshRef.Object)
	{

		FeetMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FeetMesh"));
		FeetMesh->SetSkeletalMesh(CharacterFeetMeshRef.Object);
		FeetMesh->SetupAttachment(BodyMesh);



		FeetMesh->SetLeaderPoseComponent(BodyMesh);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Basic_Animations_UE5/ABP_DDCharacter1.ABP_DDCharacter1_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UDDCharacterControlData>ShoulderDaterRef(TEXT("/Script/TheDoldrums.DDCharacterControlData'/Game/CharacterControl/ABC_Shoulder.ABC_Shoulder'"));
	if (ShoulderDaterRef.Object)
	{
		CharacterControlManager.Add(EcharacterControlType::Shoulder, ShoulderDaterRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UDDCharacterControlData>QuaterDaterRef(TEXT("/Script/TheDoldrums.DDCharacterControlData'/Game/CharacterControl/ABC_Quater.ABC_Quater'"));
	if (QuaterDaterRef.Object)
	{
		CharacterControlManager.Add(EcharacterControlType::Quater, QuaterDaterRef.Object);
	}



	//Item Actions
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ADDCharacterBase::EquipBranch)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ADDCharacterBase::EquipWaterBottle)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ADDCharacterBase::EatFood)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ADDCharacterBase::EquipClothTShirt)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ADDCharacterBase::EquipClothPants)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ADDCharacterBase::EquipClothWatch)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ADDCharacterBase::EquipClothBag)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ADDCharacterBase::EquipAxe)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ADDCharacterBase::EquipTorch)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ADDCharacterBase::EquipMachete)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ADDCharacterBase::EquipPalm)));



	//Equipment Component
	EquipmentBranch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentBranch"));
	EquipmentBranch->SetupAttachment(GetMesh(), TEXT("hand_rBranchSocket"));

	EquipmentWaterBottle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentWaterBottle"));
	EquipmentWaterBottle->SetupAttachment(GetMesh(), TEXT("hand_rWaterBottleSocket"));

	EquipmentTShirt = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EquipmentTShirt"));
	EquipmentTShirt->SetupAttachment(BodyMesh); // BodyMesh에 부착
	EquipmentTShirt->SetLeaderPoseComponent(BodyMesh); // 본 동기화

	EquipmentPants = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EquipmentPants"));
	EquipmentPants->SetupAttachment(BodyMesh); // BodyMesh에 부착
	EquipmentPants->SetLeaderPoseComponent(BodyMesh); // 본 동기화

	EquipmentWatch = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EquipmentWatch"));
	EquipmentWatch->SetupAttachment(BodyMesh); // BodyMesh에 부착
	EquipmentWatch->SetLeaderPoseComponent(BodyMesh); // 본 동기화

	EquipmentBagBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EquipmentBagBody"));
	EquipmentBagBody->SetupAttachment(BodyMesh); // BodyMesh에 부착
	EquipmentBagBody->SetLeaderPoseComponent(BodyMesh); // 본 동기화

	EquipmentBagTie = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EquipmentBagTie"));
	EquipmentBagTie->SetupAttachment(BodyMesh); // BodyMesh에 부착
	EquipmentBagTie->SetLeaderPoseComponent(BodyMesh); // 본 동기화

	EquipmentAxe = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentAxe"));
	EquipmentAxe->SetupAttachment(GetMesh(), TEXT("hand_rAxeSocket"));

	EquipmentTorchBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentTorchBody"));
	EquipmentTorchBody->SetupAttachment(GetMesh(), TEXT("hand_rTorchSocket"));

	EquipmentTorchPartC = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentTorchPartC"));
	EquipmentTorchPartC->SetupAttachment(EquipmentTorchBody);

	EquipmentTorchPartL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentTorchPartL"));
	EquipmentTorchPartL->SetupAttachment(EquipmentTorchBody);

	EquipmentMachete = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentMachete"));
	EquipmentMachete->SetupAttachment(GetMesh(), TEXT("hand_rMacheteSocket"));

	//Stat Component
	Stat = CreateDefaultSubobject<UDDCharacterStatComponent>(TEXT("Stat"));
	Stat->SetIsReplicated(true);

	////Widget Component
	HungerStat = CreateDefaultSubobject<UDDWidgetComponent>(TEXT("Widget"));
	static ConstructorHelpers::FClassFinder<UUserWidget> StatWidgetRef(TEXT("/Game/UI/WBP_UserState.WBP_UserState_C"));
	if(StatWidgetRef.Class)
	{
		CharacterStatWidgetClass = StatWidgetRef.Class;

	}
	//



}

void ADDCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Stat->OnHungerZero.AddUObject(this, &ADDCharacterBase::SetDead);
	Stat->OnThirstZero.AddUObject(this, &ADDCharacterBase::SetDead);
}

void ADDCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (CharacterStatWidgetClass)
	{
		CharacterStatWidget = CreateWidget<UUserWidget>(GetWorld(), CharacterStatWidgetClass);

		if (CharacterStatWidget)
		{
			UDDUserWidget* DDWidget = Cast<UDDUserWidget>(CharacterStatWidget);
			if (DDWidget)
			{
				DDWidget->SetOwningActor(this);
			}



			CharacterStatWidget->AddToViewport();
		}

	}

}

void ADDCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Stat->DecreaseHungerStat(1.0f);
	//Stat->DecreaseThirstStat(1.0f);

	//if (HasAuthority())
	//{
	//	// (참고: 10.0f 대신 DeltaSeconds를 곱한 값을 사용해야 함)
	//	float DecreaseRate = 1.0f; // 초당 1 감소
	//	Stat->DecreaseHungerStat(DecreaseRate * DeltaSeconds);
	//	Stat->DecreaseThirstStat(DecreaseRate * DeltaSeconds);
	//}

	//UE_LOG(LogTemp, Log, TEXT("%f"), UDSTime);

}

void ADDCharacterBase::SetCharacterControlData(const UDDCharacterControlData* CharacterControlData)
{

	//Pawn
	bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;


	//CharacterMovement
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;

}

void ADDCharacterBase::TakeItem(UDDItemDataAsset* InItemData)
{
	if (InItemData)
	{
		TakeItemActions[(uint8)InItemData->Type].ItemDelegate.ExecuteIfBound(InItemData);
	}

}


void ADDCharacterBase::EquipBranch(UDDItemDataAsset* InItemData)
{

	UDDEquipmentItemData* EquipmentItemData = Cast<UDDEquipmentItemData>(InItemData);
	if (EquipmentItemData)
	{

		if (CurrentEquippedItem && CurrentEquippedItem != InItemData)
		{
			DropItemAndClearEquippedMesh(nullptr);
		}

		if (EquipmentItemData->EquipmentStaticMesh.IsPending())
		{
			EquipmentItemData->EquipmentStaticMesh.LoadSynchronous();
			UE_LOG(LogTemp, Log, TEXT("Equip Branch"));
		}
		EquipmentBranch->SetStaticMesh(EquipmentItemData->EquipmentStaticMesh.Get());

		EquipmentNow = EItemType::Branch;
		CurrentEquippedItem = InItemData;

	}
}

void ADDCharacterBase::EquipWaterBottle(UDDItemDataAsset* InItemData)
{
	UDDEquipmentItemData* EquipmentItemData = Cast<UDDEquipmentItemData>(InItemData);
	if (EquipmentItemData)
	{
		if (CurrentEquippedItem && CurrentEquippedItem != InItemData)
		{
			DropItemAndClearEquippedMesh(nullptr);
		}

		if (EquipmentItemData->EquipmentStaticMesh.IsPending())
		{
			EquipmentItemData->EquipmentStaticMesh.LoadSynchronous();
			UE_LOG(LogTemp, Log, TEXT("Equip Bottle"));
		}
		EquipmentWaterBottle->SetStaticMesh(EquipmentItemData->EquipmentStaticMesh.Get());

		EquipmentNow = EItemType::WaterBottle;
		CurrentEquippedItem = InItemData;
	}
}


void ADDCharacterBase::EatFood(UDDItemDataAsset* InItemData)
{
	UE_LOG(LogDDCharacter, Log, TEXT("EatFood"));

}

void ADDCharacterBase::EquipClothTShirt(UDDItemDataAsset* InItemData)
{
	UDDEquipmentItemData* EquipmentItemData = Cast<UDDEquipmentItemData>(InItemData);
	if (EquipmentItemData)
	{
		if (EquipmentItemData->EquipmentSkeltalMesh.IsPending())
		{
			EquipmentItemData->EquipmentSkeltalMesh.LoadSynchronous();
		}
		EquipmentTShirt->SetSkeletalMesh(EquipmentItemData->EquipmentSkeltalMesh.Get());

	}
}

void ADDCharacterBase::EquipClothPants(UDDItemDataAsset* InItemData)
{
	UDDEquipmentItemData* EquipmentItemData = Cast<UDDEquipmentItemData>(InItemData);
	if (EquipmentItemData)
	{
		if (EquipmentItemData->EquipmentSkeltalMesh.IsPending())
		{
			EquipmentItemData->EquipmentSkeltalMesh.LoadSynchronous();
		}
		EquipmentPants->SetSkeletalMesh(EquipmentItemData->EquipmentSkeltalMesh.Get());

	}

}

void ADDCharacterBase::EquipClothWatch(UDDItemDataAsset* InItemData)
{
	UDDEquipmentItemData* EquipmentItemData = Cast<UDDEquipmentItemData>(InItemData);
	if (EquipmentItemData)
	{
		if (EquipmentItemData->EquipmentSkeltalMesh.IsPending())
		{
			EquipmentItemData->EquipmentSkeltalMesh.LoadSynchronous();
		}
		EquipmentWatch->SetSkeletalMesh(EquipmentItemData->EquipmentSkeltalMesh.Get());

	}
}

void ADDCharacterBase::EquipClothBag(UDDItemDataAsset* InItemData)
{
	UDDEquipmentItemData* EquipmentItemData = Cast<UDDEquipmentItemData>(InItemData);
	if (EquipmentItemData)
	{
		if (EquipmentItemData->EquipmentSkeltalMesh.IsPending())
		{
			EquipmentItemData->EquipmentSkeltalMesh.LoadSynchronous();
		}
		if (EquipmentItemData->EquipmentSkeltalMesh2.IsPending())
		{
			EquipmentItemData->EquipmentSkeltalMesh2.LoadSynchronous();
		}

		EquipmentBagTie->SetSkeletalMesh(EquipmentItemData->EquipmentSkeltalMesh.Get());
		EquipmentBagBody->SetSkeletalMesh(EquipmentItemData->EquipmentSkeltalMesh2.Get());
	}
}



void ADDCharacterBase::EquipAxe(UDDItemDataAsset* InItemData)
{
	UDDEquipmentItemData* EquipmentItemData = Cast<UDDEquipmentItemData>(InItemData);
	if (EquipmentItemData)
	{
		if (CurrentEquippedItem && CurrentEquippedItem != InItemData)
		{
			DropItemAndClearEquippedMesh(nullptr);
		}

		if (EquipmentItemData->EquipmentStaticMesh.IsPending())
		{
			EquipmentItemData->EquipmentStaticMesh.LoadSynchronous();
			UE_LOG(LogTemp, Log, TEXT("Equip Axe"));
		}
		EquipmentAxe->SetStaticMesh(EquipmentItemData->EquipmentStaticMesh.Get());

		EquipmentNow = EItemType::Axe;
		CurrentEquippedItem = InItemData;

	}
}

void ADDCharacterBase::EquipTorch(UDDItemDataAsset* InItemData)
{
	UDDEquipmentItemData* EquipmentItemData = Cast<UDDEquipmentItemData>(InItemData);
	if (EquipmentItemData)
	{

		if (CurrentEquippedItem && CurrentEquippedItem != InItemData)
		{
			DropItemAndClearEquippedMesh(nullptr);
		}

		if (EquipmentItemData->EquipmentStaticMesh.IsPending())
		{
			EquipmentItemData->EquipmentStaticMesh.LoadSynchronous();	
			UE_LOG(LogTemp, Log, TEXT("Equip Body"));
		}

		if (EquipmentItemData->EquipmentStaticMeshEx1.IsPending())
		{
			EquipmentItemData->EquipmentStaticMeshEx1.LoadSynchronous();
			UE_LOG(LogTemp, Log, TEXT("Equip Cloth"));
		}

		if (EquipmentItemData->EquipmentStaticMeshEx2.IsPending())
		{
			EquipmentItemData->EquipmentStaticMeshEx2.LoadSynchronous();
			UE_LOG(LogTemp, Log, TEXT("Equip Lope"));
		}

		EquipmentTorchBody->SetStaticMesh(EquipmentItemData->EquipmentStaticMesh.Get());
		EquipmentTorchPartC->SetStaticMesh(EquipmentItemData->EquipmentStaticMeshEx1.Get());
		EquipmentTorchPartL->SetStaticMesh(EquipmentItemData->EquipmentStaticMeshEx2.Get());

		EquipmentNow = EItemType::Torch;
		CurrentEquippedItem = InItemData;

	}
}

void ADDCharacterBase::EquipMachete(UDDItemDataAsset* InItemData)
{
	UDDEquipmentItemData* EquipmentItemData = Cast<UDDEquipmentItemData>(InItemData);
	if (EquipmentItemData)
	{
		if (CurrentEquippedItem && CurrentEquippedItem != InItemData)
		{
			DropItemAndClearEquippedMesh(nullptr);
		}

		if (EquipmentItemData->EquipmentStaticMesh.IsPending())
		{
			EquipmentItemData->EquipmentStaticMesh.LoadSynchronous();
			UE_LOG(LogTemp, Log, TEXT("Equip Machete"));
		}
		EquipmentMachete->SetStaticMesh(EquipmentItemData->EquipmentStaticMesh.Get());

		EquipmentNow = EItemType::Machete;
		CurrentEquippedItem = InItemData;

	}

}

void ADDCharacterBase::EquipPalm(UDDItemDataAsset* InItemData)
{
	
	UDDEquipmentItemData* EquipmentItemData = Cast<UDDEquipmentItemData>(InItemData);
	if (EquipmentItemData)
	{

		EquipmentNow = EItemType::Food;
		CurrentEquippedItem = InItemData;
	}

}

void ADDCharacterBase::SetupHungerCharacterWidget(UDDUserWidget* InUserWidget)
{
	UDDStateWidget* HungerStatWidget = Cast<UDDStateWidget>(InUserWidget);
	if (HungerStatWidget)
	{
		HungerStatWidget->SetMaxHunger(Stat->GetMaxHunger());
		HungerStatWidget->UpdateHunger(Stat->GetCurrentHunger());
		Stat->OnHungerChanged.AddUObject(HungerStatWidget, &UDDStateWidget::UpdateHunger);

	}

}

void ADDCharacterBase::SetupThirstCharacterWidget(UDDUserWidget* InUserWidget)
{
	UDDStateWidget* ThirstStatWidget = Cast<UDDStateWidget>(InUserWidget);
	if (ThirstStatWidget)
	{
		ThirstStatWidget->SetMaxThirst(Stat->GetMaxThirst());
		ThirstStatWidget->UpdateThirst(Stat->GetCurrentThirst());
		Stat->OnThirstChanged.AddUObject(ThirstStatWidget, &UDDStateWidget::UpdateThirst);

	}

}

void ADDCharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
}

void ADDCharacterBase::DropItemAndClearEquippedMesh(const AActor* DI)
{

	if (!CurrentEquippedItem)
	{
		UE_LOG(LogTemp, Log, TEXT("DropItemAndClearEquippedMesh: No Equiped item to Clear"));

		return;
	}


	const UDDEquipmentItemData* EquippedData = Cast<UDDEquipmentItemData>(CurrentEquippedItem);
	if (DI && EquippedData && EquippedData->ItemActorClass && !DI->IsA(EquippedData->ItemActorClass))
	{
		UE_LOG(LogTemp, Log, TEXT("DropItemAndClearEquippedMesh: DI does not match current equipped item."));
		return;
	}


	switch (EquipmentNow)
	{
	case EItemType::Branch:
		if (EquipmentBranch)
		{
			EquipmentNow = EItemType::None;
			EquipmentBranch->SetStaticMesh(nullptr);
		}
		break;
	case EItemType::WaterBottle:
		if (EquipmentWaterBottle)
		{
			EquipmentNow = EItemType::None;
			EquipmentWaterBottle->SetStaticMesh(nullptr);
		}
		break;
	case EItemType::Axe:
		if (EquipmentAxe)
		{
			EquipmentNow = EItemType::None;
			EquipmentAxe->SetStaticMesh(nullptr);
		}
		break;
	case EItemType::Torch:
		if (EquipmentTorchPartC)
		{
			TArray<USceneComponent*> AttachedChildren;
			EquipmentTorchPartC->GetChildrenComponents(true, AttachedChildren);

			for (USceneComponent* ChildComponent : AttachedChildren)
			{
				if (!ChildComponent)
				{
					continue;
				}

				if (ADDFireActor* AttachedFire = Cast<ADDFireActor>(ChildComponent->GetOwner()))
				{
					AttachedFire->DeactiveFire();
					AttachedFire->Destroy();


					if (UDDAnimInstance* AnimInstance = Cast<UDDAnimInstance>(BodyMesh->GetAnimInstance()))
					{
						AnimInstance->bGrabbedTorch = false;
					}

				}
			}
		}

		if (EquipmentTorchBody)
		{
			EquipmentNow = EItemType::None;
			EquipmentTorchBody->SetStaticMesh(nullptr);
		}
		if (EquipmentTorchPartC)
		{
			EquipmentTorchPartC->SetStaticMesh(nullptr);
		}
		if (EquipmentTorchPartL)
		{
			EquipmentTorchPartL->SetStaticMesh(nullptr);
		}
		break;
	case EItemType::Machete:
		if (EquipmentMachete)
		{
			EquipmentNow = EItemType::None;
			EquipmentMachete->SetStaticMesh(nullptr);
		}
		break;
	case EItemType::Food:
		if (EquipmentFoodPalm)
		{
			EquipmentNow = EItemType::None;
			EquipmentFoodPalm->SetStaticMesh(nullptr);
		}
		break;
	default:
		break;
	}

	UE_LOG(LogTemp, Log, TEXT("Drop Item In Code"));
	CurrentEquippedItem = nullptr;
	UE_LOG(LogTemp, Log, TEXT("DropItemAndClearEquippedMesh: equipped item has been cleared."));

}

void ADDCharacterBase::DistinguishItem(class UNarrativeItem* Item)
{
	if (!Item)
	{
		UE_LOG(LogDDCharacter, Warning, TEXT("DistinguishItem: Item is Null."));
		return;
	}

	ResolveItemTypeFromNarrativeItem(Item);







	/*UDDItemDataAsset* ItemData = LoadDataAssetForType(ItemType);
	if (!ItemData)
	{
		UE_LOG(LogDDCharacter, Warning, TEXT("DistinguishItem: no data asset mapping for item type %d (%s)."), static_cast<int32>(ItemType), *GetNameSafe(Item->GetClass()));
		return;
	}

	TakeItem(ItemData);*/

}

void ADDCharacterBase::ResolveItemTypeFromNarrativeItem(const UNarrativeItem* Item)
{
	const FString NormalizedDisplayName = Item->DisplayName.ToString().ToLower();
		
	if (NormalizedDisplayName.Contains(TEXT("OpendPalm")))
	{
		UE_LOG(LogTemp, Warning, TEXT("OpendPalmUsed!!"));

		Stat->IncreaseHungerStat(10.0f);
		Stat->IncreaseThirstStat(10.0f);

		return;
	}

	//음식관련은 return을 줘서 안꼬이게 할려면 위에다가 food

	if (CurrentEquippedItem)
	{
		DropItemAndClearEquippedMesh(nullptr);
	}

	const TCHAR* ItemDataAssetPath = nullptr;

	if (NormalizedDisplayName.Contains(TEXT("branch")))
	{
		ItemDataAssetPath = TEXT("/Game/Item/Equipment/DDIW_Branch.DDIW_Branch");
	}
	else if (NormalizedDisplayName.Contains(TEXT("waterbottle")) || NormalizedDisplayName.Contains(TEXT("water bottle")))
	{
		ItemDataAssetPath = TEXT("/Game/Item/Equipment/DDIW_WaterBottle.DDIW_WaterBottle");
	}
	else if (NormalizedDisplayName.Contains(TEXT("axe")))
	{
		ItemDataAssetPath = TEXT("/Game/Item/Equipment/DDIW_Axe.DDIW_Axe");
	}
	else if (NormalizedDisplayName.Contains(TEXT("torch")))
	{
		ItemDataAssetPath = TEXT("/Game/Item/Equipment/DDIW_Torch.DDIW_Torch");
	}
	else if (NormalizedDisplayName.Contains(TEXT("machete")))
	{
		ItemDataAssetPath = TEXT("/Game/Item/Equipment/DDIW_Machete.DDIW_Machete");
	}

	if (!ItemDataAssetPath)
	{
		UE_LOG(LogDDCharacter, Warning, TEXT("DistinguishItem: unsupported item for equip (%s)."), *Item->DisplayName.ToString());
		return;
	}

	UDDItemDataAsset* ItemData = LoadObject<UDDItemDataAsset>(nullptr, ItemDataAssetPath);
	if (!ItemData)
	{
		UE_LOG(LogDDCharacter, Warning, TEXT("DistinguishItem: failed to load item data asset path (%s)."), ItemDataAssetPath);
		return;
	}

	TakeItem(ItemData);


}
