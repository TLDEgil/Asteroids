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
	SetRateOfFire(ROF);

	// ...
}

// Called every frame
void UBasePlayerShipGun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentFireDelay -= DeltaTime;
}

void UBasePlayerShipGun::Fire(FVector InheritedVelocity)
{
	if (CurrentFireDelay < 0) // If can fire again
	{
		
		if (!BulletToFire)
		{
			UE_LOG(LogTemp, Error, TEXT("WeaponSystem on %s has no bullet set"), *GetOwner()->GetName());
			return;
		}
		ABaseBullet * Bullet = GetWorld()->SpawnActor<ABaseBullet>(BulletToFire, GetOwner()->GetActorTransform());
		Bullet->SetData(BulletRange, BulletSpeed, BulletDamage, InheritedVelocity, GetOwner()->GetActorForwardVector());
		Bullet->AddActorLocalOffset(FireLocation);
		Bullets.Add(Bullet);
		CurrentFireDelay = 0.0f + FireDelay;
		NextBulletID++;
		UE_LOG(LogTemp, Warning, TEXT("Bang: %i"), NextBulletID);
	}
}

int UBasePlayerShipGun::GetRateOfFire()
{
	return ROF;
}

void UBasePlayerShipGun::SetRateOfFire(int NewRateOfFire)
{
	ROF = NewRateOfFire;
	FireDelay = 60.f / NewRateOfFire;
	CurrentFireDelay = FireDelay;
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


