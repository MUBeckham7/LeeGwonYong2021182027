// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Perception/AISense_Hearing.h"
#include "ABItemSiren.generated.h"


UCLASS()
class WMA_API AABItemSiren : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABItemSiren();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Replicated, Category = Box)
    TObjectPtr<class UBoxComponent> CollisionBox;

    UPROPERTY(VisibleAnywhere, Replicated, Category = "Mesh")
    class UStaticMeshComponent* SirenMesh;

    UPROPERTY(EditAnywhere, Replicated, Category = Item)
    TObjectPtr<class UABItemData>Item;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

    UFUNCTION()
    void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UStaticMesh* TempBoxMesh;

    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UWidgetComponent> TextE;

    TSubclassOf<UUserWidget> InteractionButtonWidgetClass;

    UUserWidget* ItemWidget;

    AActor* PlayerActor;

    bool bIsHolding = false;
    bool bIsHoldOnce = false;
    void MakeSound();
    void ClarksionOn();

public:
    void OnInteract();

    UAISense_Hearing* AISenseHearing;
protected:
    UFUNCTION(Client, Reliable)
    void ServerRPCInteract();
    UFUNCTION(NetMulticast, Reliable)
    void MulticastRPCInteract();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    UPROPERTY(VisibleAnywhere, Replicated, Category = "Mesh")
    uint8 bIsVisible : 1;

    void ATDTSiren();

    UFUNCTION(Client, Reliable)
    void ServerRPCOverlap(AActor* OtherActor);
    UFUNCTION(NetMulticast, Reliable)
    void MulticastRPCOverlap(AActor* OtherActor);

    UFUNCTION(Client, Reliable)
    void ServerRPCOverlapEnd(AActor* OtherActor);
    UFUNCTION(NetMulticast, Reliable)
    void MulticastRPCOverlapEnd(AActor* OtherActor);

    UFUNCTION(Server, Reliable)
    void ServerRPCClarksion();
    UFUNCTION(NetMulticast, Reliable)
    void MulticastRPCClarksion();

    UPROPERTY(VisibleAnywhere, Replicated, Category = "Sound");
    class USoundBase* Clarksion;

    UPROPERTY(VisibleAnywhere, Replicated, Category = "Sound")
    class USoundAttenuation* ClarksionAtt;

    int cnt;
};
