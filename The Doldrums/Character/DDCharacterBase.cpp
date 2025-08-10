// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DDCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMesh.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DDCharacterControlData.h"
#include "Item/DDEquipmentItemData.h"
#include "Components/WidgetComponent.h"

DEFINE_LOG_CATEGORY(LogDDCharacter);

// Sets default values
ADDCharacterBase::ADDCharacterBase()
{
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




}

void ADDCharacterBase::BeginPlay()
{
	Super::BeginPlay();


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
		if (EquipmentItemData->EquipmentStaticMesh.IsPending())
		{
			EquipmentItemData->EquipmentStaticMesh.LoadSynchronous();
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
		if (EquipmentItemData->EquipmentStaticMesh.IsPending())
		{
			EquipmentItemData->EquipmentStaticMesh.LoadSynchronous();
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
		if (EquipmentItemData->EquipmentStaticMesh.IsPending())
		{
			EquipmentItemData->EquipmentStaticMesh.LoadSynchronous();
		}
		EquipmentAxe->SetStaticMesh(EquipmentItemData->EquipmentStaticMesh.Get());

		EquipmentNow = EItemType::Axe;
		CurrentEquippedItem = InItemData;

	}
}

