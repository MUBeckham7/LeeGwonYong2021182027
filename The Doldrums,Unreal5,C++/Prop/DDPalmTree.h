// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/DDInteractionItem.h"
#include "DDPalmTree.generated.h"

/**
 * 
 */
class ADDPalm;

UCLASS()
class THEDOLDRUMS_API ADDPalmTree : public ADDInteractionItem 
{
	GENERATED_BODY()

public:

	ADDPalmTree();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Box)
	TObjectPtr<class UBoxComponent>TriggerTree;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> Text;

	TSubclassOf<UUserWidget> InteractionItemWidgetClass;

	UUserWidget* ItemWidget;

	AActor* PlayerActor;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ADDPalm> PalmClass;




protected:

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	void OnInteract();

	void FallFruit();

	void GenerateRandomSpawnSchedule();

	void SpawnPalm();

	UPROPERTY()
	TObjectPtr<class ADDCharacterBase> CachedPlayer;

	int32 AccumulateDays = 0;
	float CurrentTime = 0.0f;
	float PreviousTime = -1.0f;

	TArray<int32> SpawnDays;
	int32 GeneratedThisYear = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxPalmPerYear = 12;


	TDoubleLinkedList<ADDPalm*> CoconutList;



};
