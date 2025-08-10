// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/DDInteractionItem.h"
#include "DDTent.generated.h"

/**
 * 
 */
UCLASS()
class THEDOLDRUMS_API ADDTent : public ADDInteractionItem
{
	GENERATED_BODY()
	
public:

	ADDTent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Tent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = Box)
	TObjectPtr<class UBoxComponent> TriggerTent;

	UPROPERTY(VisibleAnywhere,BluePrintReadOnly,Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> Text;

	TSubclassOf<UUserWidget> InteractionItemWidgetClass;

	UUserWidget* ItemWidget;

	AActor* PlayerActor;

protected:

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	void OnInteract();

};
