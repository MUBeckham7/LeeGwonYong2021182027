// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DDEquipClothPants.generated.h"

UCLASS()
class THEDOLDRUMS_API ADDEquipClothPants : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADDEquipClothPants();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class USkeletalMeshComponent> Pants;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Box)
	TObjectPtr<class UBoxComponent> TriggerPants;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> Text;

	TSubclassOf<UUserWidget> InteractionItemWidgetClass;

	UUserWidget* ItemWidget;

	AActor* PlayerActor;

	UPROPERTY(EditAnywhere, Category = Item)
	TObjectPtr<class UDDItemDataAsset> Item;

protected:

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	void OnInteract();



};
