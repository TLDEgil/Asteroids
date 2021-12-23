// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerShipGun.h"

// Sets default values for this component's properties
UBasePlayerShipGun::UBasePlayerShipGun()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UBasePlayerShipGun::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UBasePlayerShipGun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UBasePlayerShipGun::GetRateOfFire()
{
	return ROF;
}

void UBasePlayerShipGun::SetRateOfFire(int NewRateOfFire)
{
	ROF = NewRateOfFire;
	FireDelay = ROF / 60.0f;
}

float UBasePlayerShipGun::GetBulletVelocity()
{
	return BulletSpeed;
}

void UBasePlayerShipGun::SetBulletVelocity(float NewBulletVelocity)
{
	BulletSpeed = NewBulletVelocity;
}

float UBasePlayerShipGun::GetBulletDamage()
{
	return BulletDamage;
}

void UBasePlayerShipGun::SetBulletDamage(float NewBulletDamage)
{
	BulletDamage = NewBulletDamage;
}

float UBasePlayerShipGun::GetBulletRange()
{
	return BulletRange;
}

void UBasePlayerShipGun::SetBulletRange(float NewBulletRange)
{
	BulletRange = NewBulletRange;
}


