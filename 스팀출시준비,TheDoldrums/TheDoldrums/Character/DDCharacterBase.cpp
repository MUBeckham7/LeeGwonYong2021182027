// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DDCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GroomComponent.h"
#include "GroomBindingAsset.h"
#include "Engine/SkeletalMesh.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DDCharacterControlData.h"

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
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

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

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterLegsMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/MetaHumans/Common/Male/Medium/NormalWeight/Shoes/CasualSneakers/m_med_nrw_shs_casualsneakers_Cinematic.m_med_nrw_shs_casualsneakers_Cinematic'"));
	//if (CharacterLegsMeshRef.Object)
	//{

	//	LegsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LegsMesh"));
	//	LegsMesh->SetSkeletalMesh(CharacterLegsMeshRef.Object);
	//	LegsMesh->SetupAttachment(BodyMesh);



	//	TorsoMesh->SetMasterPoseComponent(BodyMesh);
	//}

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterTorsoMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/MetaHumans/Common/Male/Medium/NormalWeight/Shoes/CasualSneakers/m_med_nrw_shs_casualsneakers_Cinematic.m_med_nrw_shs_casualsneakers_Cinematic'"));
	//if (CharacterTorsoMeshRef.Object)
	//{

	//	TorsoMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TorsoMesh"));
	//	TorsoMesh->SetSkeletalMesh(CharacterTorsoMeshRef.Object);
	//	TorsoMesh->SetupAttachment(BodyMesh);



	//	TorsoMesh->SetMasterPoseComponent(BodyMesh);
	//}


	//static ConstructorHelpers::FObjectFinder<UGroomBindingAsset> BeardBinding(TEXT("/Script/HairStrandsCore.GroomBindingAsset'/Game/MetaHumans/Nasim/MaleHair/GroomBinding/Beard_M_Curly_Binding.Beard_M_Curly_Binding'"));
	//if (BeardBinding.Object) {
	//	Beard = CreateDefaultSubobject<UGroomBindingAsset>(TEXT("Beard"));
	//	Beard->
	//}
	//


	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Characters/Mannequins/Animations/ABP_Quinn.ABP_Quinn_C"));
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
