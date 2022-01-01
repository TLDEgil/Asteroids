// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"

// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAsteroid::RegisterHitFromBullet(float BulletDamage)
{
	Health -= BulletDamage;
	CurrentScale = FMath::Lerp(BaseScale, SizeAtDeathScale, 1-(Health / MaxHealth));
	UE_LOG(LogTemp, Display, TEXT("Took % f Damage, Current Health: %f, CurrentScale %f"), BulletDamage, Health, CurrentScale);
	SetActorRelativeScale3D(FVector(CurrentScale));
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	XRotationSpeed = FMath::RandRange(2, 30); // Rotation speed in Degreees/S
	YRotationSpeed = FMath::RandRange(2, 30); // Rotation speed in Degreees/S
	ZRotationSpeed = FMath::RandRange(2, 30); // Rotation speed in Degreees/S
	MaxHealth = Health;
	BaseScale = GetActorScale3D().Size();
	SizeAtDeathScale *= BaseScale;
	CurrentScale = FMath::Lerp(BaseScale, SizeAtDeathScale, 1 - (Health / MaxHealth));
	SetActorScale3D(FVector(CurrentScale)); // ????? Without this asteroid jumps up in size when hit the first time
	UE_LOG(LogTemp, Display, TEXT("Data for %s"), *GetName());
	UE_LOG(LogTemp, Display, TEXT("SizeAtDeathScale is	%f"), SizeAtDeathScale);
	UE_LOG(LogTemp, Display, TEXT("BaseScale is			%f"), BaseScale);
	UE_LOG(LogTemp, Display, TEXT("CurrentScale is		%f"), CurrentScale);
	UE_LOG(LogTemp, Display, TEXT("MaxHealth is			%f"), MaxHealth);
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator TickRotation(XRotationSpeed * DeltaTime, YRotationSpeed * DeltaTime, ZRotationSpeed * DeltaTime);

	AddActorWorldRotation(TickRotation);
}

