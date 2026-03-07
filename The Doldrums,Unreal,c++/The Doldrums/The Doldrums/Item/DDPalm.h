// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/DDItemDataAsset.h"
#include "DDPalm.generated.h"

/**
 * 
 */

class ADDPalmTree;
class ADDOpendPalm;


UCLASS()
class THEDOLDRUMS_API ADDPalm : public AActor
{
	GENERATED_BODY()
	
public:

	ADDPalm();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Fruit;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Box)
	TObjectPtr<class UBoxComponent>TriggerFruit;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> Text;

	TSubclassOf<UUserWidget> InteractionItemWidgetClass;

	UUserWidget* ItemWidget;

	AActor* PlayerActor;

	UPROPERTY()
	TObjectPtr<class ADDPlayerController> CachedPlayerController;

	UPROPERTY(EditAnywhere, Category = Item)
	UDDItemDataAsset* Item;

	UPROPERTY(EditAnywhere, Category = Item)
	TSubclassOf<class UNarrativeItem> ItemDDPalmClass;

	UPROPERTY(EditAnywhere, Category = Palm)
	TSubclassOf<ADDOpendPalm> OpenPalmClass;

protected:

	UFUNCTION()
	void OnOverlapBeginFruit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OnOverlapEndFruit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:

	void OnInteract();

	ADDPalmTree* OwnerTree;

	UPROPERTY()
	bool bShouldFall = false;

	UPROPERTY()
	bool bIsFalling = false;

	void StartFall();

	void ReplaceWithOpenPalm();


};
