// Fill out your copyright notice in the Description page of Project Settings.


#include "Weather/DDWeather.h"

// Sets default values
ADDWeather::ADDWeather()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADDWeather::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADDWeather::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

