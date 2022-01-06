// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerShipMovementComponent.h"
#include "PlayerShipReplicationComponent.h"
#include "PlayerShipEngineComponent.h"
#include "BasePlayerShipGun.h"

#include "BasePlayerShip.generated.h"

UCLASS()
class ASTEROIDS_API ABasePlayerShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePlayerShip();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UPlayerShipMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UPlayerShipReplicationComponent* ReplicationComponent;

	// Engine component and it's related functions
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UPlayerShipEngineComponent* EngineComponent;

	float GetThrust() const;
	void SetTargetThrust(float NewThrust);

	void SetPitchAxis(float PitchAxis);
	void SetYawAxis(float YawAxis);
	void SetRollAxis(float RollAxis);

	float GetMaxThrust() const;
	void SetMaxThrust(float NewMaxThrust);

	float GetCurrentThrust() const;

	float GetThrustChangeSpeed() const;
	void SetThrustChangeSpeed(float NewThrustChangeSpeed);

	float GetBaseMass() const;
	void SetBaseMass(float NewBaseMass);

	// GunComponent and it's related functions
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBasePlayerShipGun* WeaponSystem;

	void Fire(float Fire);

	int GetRateOfFire() const;
	void SetRateOfFire(int NewRateOfFire);

	float GetBulletVelocity() const;
	void SetBulletVelocity(float NewBulletVelocity);

	float GetBulletDamage() const;
	void SetBulletDamage(float NewBulletDamage);

	float GetBulletRange() const;
	void SetBulletRange(float NewBulletRange);

	// Health and it's related unctions
	float GetMaxHealth() const;
	void SetMaxHealth(float NewMaxHealth);

	float GetCurrentHealth() const;
	void ChangeCurrentHealth(float Change);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		float BaseMass = 30000; // Mass in KG

	UPROPERTY(EditAnywhere)
		float MaxHealth;
	UPROPERTY(EditAnywhere)
		float CurrentHealth;
};
