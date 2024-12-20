// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WMACharacterPlayer.h"
#include "Interface/ABCharacterItemInterface.h"
#include "GameFramework/Actor.h"
#include "ABItemGun.generated.h"

UCLASS()
class WMA_API AABItemGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABItemGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = Box)
    TObjectPtr<class UBoxComponent> Trigger;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Box)
    TObjectPtr<class UStaticMeshComponent> Mesh;

    UPROPERTY(VisibleAnywhere, Category = Effect)
    TObjectPtr<class UParticleSystemComponent> Effect;

    UPROPERTY(EditAnywhere, Category = Item)
    TObjectPtr<class UABItemData>Item;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* StaticMeshComponent;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

    UFUNCTION()
    void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void OnEffectFinished(class UParticleSystemComponent* ParticleSystem);

    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UWidgetComponent> TextE;

    TSubclassOf<UUserWidget> InteractionItemWidgetClass;

    UUserWidget* ItemWidget;

    AActor* PlayerActor;
public:
    void OnInteract();

};
