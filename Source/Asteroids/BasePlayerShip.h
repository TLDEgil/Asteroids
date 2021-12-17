// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerShipMovementComponent.h"
#include "PlayerShipReplicationComponent.h"
#include "PlayerShipEngineComponent.h"

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
	void SetThrust(float NewThrust);

	float GetMaxThrust() const;
	void SetMaxThrust(float NewMaxThrust);

	float GetThrustChangeSpeed() const;
	void SetThrustChangeSpeed(float NewThrustChangeSpeed);

	float GetBaseMass() const;
	void SetBaseMass(float NewBaseMass);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		float BaseMass; // Mass in KG


};
