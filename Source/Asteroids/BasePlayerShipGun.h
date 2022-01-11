// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseBullet.h"
#include "BasePlayerShipGun.generated.h"

USTRUCT()
struct FBulletFireInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		float TimeCreated;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDS_API UBasePlayerShipGun : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBasePlayerShipGun();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Fire(FVector InheritedVelocity);

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
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
		FVector FireLocation;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseBullet> BulletToFire = nullptr;
	
	UPROPERTY()
		TArray<ABaseBullet*> Bullets;

	unsigned int NextBulletID = 0;

	UPROPERTY(EditAnywhere)// Rate Of Fire, in rounds per minute
		int ROF = 300;  
	// Time left in seconds until the next round can be fired
	float CurrentFireDelay = 0.0f;
	// How much time in seconds must pass betwen each round
	float FireDelay = 1.0f; 

	UPROPERTY(EditAnywhere)
		// Speed in M/s
		float BulletSpeed = 300; 

	UPROPERTY(EditAnywhere)
		// Damage
		float BulletDamage = 100; 

	UPROPERTY(EditAnywhere)
		// Range in KM
		float BulletRange = 3; 


		
};
