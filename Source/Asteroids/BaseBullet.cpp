// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"

// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseBullet::Move(float DeltaTime)
{
	FVector Translation = Forwards * DeltaTime * Velocity * 100;
	Range -= Velocity * DeltaTime * 100;
	FHitResult Hit;
	AddActorWorldOffset(Translation, true, &Hit);

	if (Hit.IsValidBlockingHit())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Impact"));
		Destroy();
	}
	if (Range < 0)
	{
		Destroy();
	}
}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void ABaseBullet::SetData(float ArgRange, float ArgVelocity, float ArgDamage, FVector ArgForwards)
{
	Range = ArgRange * 1000;
	Velocity = ArgVelocity;
	Damage = ArgDamage;
	Forwards = ArgForwards;
}

