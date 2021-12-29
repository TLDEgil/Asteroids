// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseBullet.h"
#include "BasePlayerShipGun.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDS_API UBasePlayerShipGun : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBasePlayerShipGun();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Fire();

	int GetRateOfFire();
	void SetRateOfFire(int NewRateOfFire);

	float GetBulletVelocity();
	void SetBulletVelocity(float NewBulletVelocity);

	float GetBulletDamage();
	void SetBulletDamage(float NewBulletDamage);

	float GetBulletRange();
	void SetBulletRange(float NewBulletRange);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseBullet> BulletToFire = nullptr;

	unsigned int NextBulletID = 0;

	UPROPERTY(EditAnywhere)
		int ROF = 5000; // Rate Of Fire, in rounds per minute
	float CurrentFireDelay = 0.0f; // Time left in seconds until the next round can be fired
	float FireDelay = 1.0f; // How much time in seconds must pass betwen each round

	UPROPERTY(EditAnywhere)
		float BulletSpeed = 100; // Speed in M/s

	UPROPERTY(EditAnywhere)
		float BulletDamage = 100; // Damage

	UPROPERTY(EditAnywhere)
		float BulletRange = 2; // Range in KM


		
};
