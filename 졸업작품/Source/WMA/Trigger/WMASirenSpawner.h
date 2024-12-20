// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WMASirenSpawner.generated.h"

UCLASS()
class WMA_API AWMASirenSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWMASirenSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Replicated, Category = Box)
    TObjectPtr<class UBoxComponent> CollisionBox;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

    UFUNCTION()
    void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UStaticMesh* TempBoxMesh;

    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UWidgetComponent> TextE;

    TSubclassOf<UUserWidget> InteractionButtonWidgetClass;

    UUserWidget* ItemWidget;
    bool bIsHolding = false;
    bool bIsHoldOnce = false;
    AActor* PlayerActor;

public:
    void OnInteract();

protected:
 /*   UFUNCTION(Client, Reliable)
    void ServerRPCInteract();
    UFUNCTION(NetMulticast, Reliable)
    void MulticastRPCInteract();*/

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    UPROPERTY(VisibleAnywhere, Replicated, Category = "Mesh")
    uint8 bIsVisible : 1;

    UFUNCTION(Server, Reliable)
    void ServerRPCSpawn();
    UFUNCTION(NetMulticast, Reliable)
    void MulticastRPCSpawn();
};
