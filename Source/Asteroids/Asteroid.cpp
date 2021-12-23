// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"

// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	XRotationSpeed = FMath::RandRange(2, 30); // Rotation speed in Degreees/S
	YRotationSpeed = FMath::RandRange(2, 30); // Rotation speed in Degreees/S
	ZRotationSpeed = FMath::RandRange(2, 30); // Rotation speed in Degreees/S
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator TickRotation(XRotationSpeed * DeltaTime, YRotationSpeed * DeltaTime, ZRotationSpeed * DeltaTime);

	AddActorWorldRotation(TickRotation);
}

