// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/DDTree.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
ADDTree::ADDTree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Fruit = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fruit"));

	RootComponent = Body;
	Fruit->SetupAttachment(Body);
	Fruit->SetRelativeLocation(FVector(102.0f, 40.0f, 569.0f));
	Fruit->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>BodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/TropicalIsland/Meshes/SM_PalmTreeB.SM_PalmTreeB'"));
	if (BodyMeshRef.Object) {
		Body->SetStaticMesh(BodyMeshRef.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>FruitMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Prop/coconut123.coconut123'"));
	if (FruitMeshRef.Object) {
		Fruit->SetStaticMesh(FruitMeshRef.Object);
	}

}

// Called when the game starts or when spawned
void ADDTree::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADDTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

