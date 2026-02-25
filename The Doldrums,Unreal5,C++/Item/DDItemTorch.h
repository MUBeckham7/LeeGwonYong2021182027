// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/DDItemDataAsset.h"
#include "DDItemTorch.generated.h"

UCLASS()
class THEDOLDRUMS_API ADDItemTorch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDItemTorch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Torch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Cloth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Lope;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Box)
	TObjectPtr<class UBoxComponent> TriggerTorch;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> Text;

	TSubclassOf<UUserWidget> InteractionItemWidgetClass;

	UUserWidget* ItemWidget;

	AActor* PlayerActor;

	UPROPERTY(EditAnywhere, Category = Item)
	UDDItemDataAsset* Item;

	UPROPERTY(EditAnywhere, Category = Item)
	TSubclassOf<class UNarrativeItem> ItemDDTorchClass;


protected:

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	void OnInteract();


	UPROPERTY()
	TObjectPtr<class ADDFireActor> SpawnedFireActor = nullptr;
};
