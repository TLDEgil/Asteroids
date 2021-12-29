// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerShipEngineComponent.h"
#include "PlayerShipMovementComponent.generated.h"

// MovementData structure for net replication
USTRUCT()
struct FPlayerShipMove
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		float PitchRate; // Rate the ship is currently pitching at
	UPROPERTY()
		float YawRate; // Rate the ship is currently yawing at
	UPROPERTY()
		float RollRate; // Rate the ship is currently rolling at
	UPROPERTY()
		float Throttle; // What the ship's throttle is currently set to
	UPROPERTY()
		FTransform Location; // Ship transform
	UPROPERTY()
		float TimeCreated; // Time the move is created
	UPROPERTY()
		float DeltaTime; // Delta time
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDS_API UPlayerShipMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerShipMovementComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FPlayerShipMove GetLastMove();
	FPlayerShipMove CreateMove(float DeltaTime);
	void SimulateMove(const FPlayerShipMove& Move);

	void ApplyMovement(const FPlayerShipMove& Move);
	void ApplyRotation(const FPlayerShipMove& Move);

	FVector GetVelocity() const;
	void SetVelocity(FVector NewVelocity);

	float GetThrottle() const;
	void SetThrottle(float NewThrottle);

	float GetPitch() const;
	void SetPitch(float NewPitch);
	float GetYaw() const;
	void SetYaw(float NewYaw);
	float GetRoll() const;
	void SetRoll(float NewRoll);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



private:
	void UpdateValues(float DeltaTime);

	UPROPERTY()
	UPlayerShipEngineComponent* EngineComponent;

	FPlayerShipMove LastMove;
	FVector Velocity;	
	float MaxSpeed = 30;

	UPROPERTY()
		float CurrentPitchRate;
	UPROPERTY(EditAnywhere)
		float PitchRateIncrease = 90; // Rate pitch increase in degrees/second
	UPROPERTY()
		float CurrentYawRate;
	UPROPERTY(EditAnywhere)
		float YawRateIncrease = 90; // Rate yaw increase in degrees/second
	UPROPERTY()
		float CurrentRollRate;
	UPROPERTY(EditAnywhere)
		float RollRateIncrease = 90; // Rate roll increase in degrees/second

	UPROPERTY()
		float Pitch; // How much pitch acceleration is being used on a scale of -1.0f to 1.0f
	UPROPERTY()
		float Yaw; // How much raw acceleration is being used on a scale of -1.0f to 1.0f
	UPROPERTY()
		float Roll; // How much roll acceleration is being used on a scale of -1.0f to 1.0f
	UPROPERTY()
		float Throttle; // How much acceleration is being used on a scale of -1.0f to 1.0f
};
