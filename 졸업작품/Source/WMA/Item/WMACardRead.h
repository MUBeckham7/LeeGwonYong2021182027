// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimeLineComponent.h"
#include "WMACardRead.generated.h"

UCLASS()
class WMA_API AWMACardRead : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWMACardRead();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* Button;

protected:
	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UBoxComponent> CollisionBox;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> TextE;
	TSubclassOf<UUserWidget> InteractionButtonWidgetClass;

	UUserWidget* ButtonWidget;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	TArray<AActor*> EVDoors;

	UPROPERTY(EditAnyWhere)
	FTimeline Timeline;				// Timeline ����

	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;			// Timeline Ŀ��

	bool bIsOpened = false;
public:
	UFUNCTION()
	void OpenDoor(float Alpha);

	UFUNCTION()
	void OnInteract();
};
