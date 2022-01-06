// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerShipMovementComponent.h"
#include "PlayerShipReplicationComponent.generated.h"

USTRUCT()
struct FPlayerShipState
{
	GENERATED_USTRUCT_BODY()

		/*
		UPROPERTY()
			float LastMovePitchRate; // Rate the ship is currently pitching at
		UPROPERTY()
			float LastMoveYawRate; // Rate the ship is currently yawing at
		UPROPERTY()
			float LastMoveRollRate; // Rate the ship is currently rolling at
		UPROPERTY()
			FVector LastMoveVelocity; // What the ship's throttle is currently set to
		UPROPERTY()
			FTransform LastMoveTransform; // Ship transform
		UPROPERTY()
			float LastMoveTimeCreated; // Time the move is created
		UPROPERTY()
			float LastMoveDeltaTime; // Delta time
		*/
	UPROPERTY()
		FPlayerShipMove LastMove;
	UPROPERTY()
		float ShipCurrentHealth;
	UPROPERTY()
		float ShipMaxHealth;
};

struct FHermiteCubicSpline
{
	FVector StartLocation, StartDerivative, TargetLocation, TargetDerivative;

	FVector InterpolateLocation(float LerpRatio) const
	{
		return FMath::CubicInterp(StartLocation, StartDerivative, TargetLocation, TargetDerivative, LerpRatio);
	}
	FVector InterpolateDerivative(float LerpRatio) const
	{
		return FMath::CubicInterpDerivative(StartLocation, StartDerivative, TargetLocation, TargetDerivative, LerpRatio);
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDS_API UPlayerShipReplicationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerShipReplicationComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void GetLifeTimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		UPlayerShipMovementComponent* MovementComponent;

	
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_SendMove(FPlayerShipMove Move);

	void ClearAcknowlegedMoves(const float& LastAcknowlegedMoveTimeCreated);
	void UpdateServerState(const FPlayerShipMove Move);
	void ClientTick(float DeltaTime);

	UFUNCTION()
	void OnRep_ServerState();

	UPROPERTY(ReplicatedUsing = OnRep_ServerState)
		FPlayerShipState ServerState;

	void SimulatedProxy_OnRep_ServerState();
	void AutonomousProxy_OnRep_ServerState();


	void InterpolateLocation(const FHermiteCubicSpline& Spline, float LerpRatio);
	void InterpolateRotation(float LerpRatio);
	void InterpolateDerivative(const FHermiteCubicSpline& Spline, float LerpRatio, float VelocityToDerivative);
	void CreateSpline(FHermiteCubicSpline& Spline, float VelocityToDerivative);

	TArray<FPlayerShipMove> UnacknowlegedMoves;
	float ClientTimeSinceLastRecievedUpdate;
	float ClientTimeBetweenLastUpdates;
	FTransform ClientStartTransform;
	FVector ClientStartVelocity;	
};