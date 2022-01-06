// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShipReplicationComponent.h"
#include "Net/UnrealNetwork.h"
#include "BasePlayerShip.h"


FString GetEnumText(ENetRole Role)
{
	switch (Role)
	{
	case ROLE_None:
		return "None";
	case ROLE_SimulatedProxy:
		return "Simulated Proxy";
	case ROLE_AutonomousProxy:
		return "Autonomus Proxy";
	case ROLE_Authority:
		return "Authority";
	default:
		return "Error";
	}
}

// Called every frame
void UPlayerShipReplicationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (MovementComponent == nullptr) return;

	FPlayerShipMove LastMove = MovementComponent->GetLastMove();
	UE_LOG(LogTemp, Warning, TEXT("%s Role: %s\t\tRemoteRole:%s"), *GetOwner()->GetName(), *GetEnumText(GetOwnerRole()), *GetEnumText(GetOwner()->GetRemoteRole()));

	// If not server and controlling pawn
	if (GetOwnerRole() == ROLE_AutonomousProxy)
	{
		//UE_LOG(LogTemp, Display, TEXT("Sending Move from %s"), *GetOwner()->GetName());
		UnacknowlegedMoves.Add(LastMove);
		Server_SendMove(LastMove);
	}
	// If server and controlling pawn
	if (GetOwner()->GetRemoteRole() == ROLE_SimulatedProxy)
	{
		//UE_LOG(LogTemp, Display, TEXT("Updating ServerState from %s"), *GetOwner()->GetName());
		UpdateServerState(LastMove);
	}
	// If not server and not controlling pawn
	if (GetOwnerRole() == ROLE_SimulatedProxy)
	{
		//UE_LOG(LogTemp, Display, TEXT("ClientTick on %s"), *GetOwner()->GetName());
		ClientTick(DeltaTime);
	}
}

void UPlayerShipReplicationComponent::GetLifetimeReplicatedProps(TArray < FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPlayerShipReplicationComponent, ServerState);
}

// Sets default values for this component's properties
UPlayerShipReplicationComponent::UPlayerShipReplicationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPlayerShipReplicationComponent::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent = GetOwner()->FindComponentByClass<UPlayerShipMovementComponent>();
	if (!MovementComponent) UE_LOG(LogTemp, Error, TEXT("ReplicationComponent on %s could not find MovementComponent"), *GetOwner()->GetName());
}

void UPlayerShipReplicationComponent::Server_SendMove_Implementation(const FPlayerShipMove Move)
{
	if (MovementComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No ReplicationComponent on %s has no MovementComponent"), *GetOwner()->GetName());
		return;
	}

	MovementComponent->SimulateMove(Move);

	UpdateServerState(Move);
}

bool UPlayerShipReplicationComponent::Server_SendMove_Validate(const FPlayerShipMove Move)
{
	return true; // TODO validate
}

void UPlayerShipReplicationComponent::ClearAcknowlegedMoves(const float& LastAcknowlegedMoveTimeCreated)
{
	TArray<FPlayerShipMove> NewUncknowlegedMoves;
	for (const FPlayerShipMove& Move : UnacknowlegedMoves)
	{
		if (Move.TimeCreated > LastAcknowlegedMoveTimeCreated)
		{
			NewUncknowlegedMoves.Add(Move);
		}
	}
	UnacknowlegedMoves = NewUncknowlegedMoves;
}

void UPlayerShipReplicationComponent::UpdateServerState(const FPlayerShipMove Move)
{
	ServerState.LastMove.PitchRate = Move.PitchRate; // Rate the ship is currently pitching at
	ServerState.LastMove.YawRate = Move.YawRate; // Rate the ship is currently yawing at
	ServerState.LastMove.RollRate = Move.RollRate; // Rate the ship is currently rolling at
	ServerState.LastMove.Velocity = Move.Velocity; // What the ship's throttle is currently set to
	ServerState.LastMove.Transform = Move.Transform; // Ship transform
	ServerState.LastMove.TimeCreated = Move.TimeCreated; // Time the move is created
	ServerState.LastMove.DeltaTime = Move.DeltaTime; // Delta time
	ServerState.LastMove.Thrust = GetOwner<ABasePlayerShip>()->GetCurrentThrust();
	ServerState.ShipCurrentHealth = GetOwner<ABasePlayerShip>()->GetCurrentHealth();
	ServerState.ShipMaxHealth = GetOwner<ABasePlayerShip>()->GetMaxHealth();
}

void UPlayerShipReplicationComponent::ClientTick(float DeltaTime)
{
	ClientTimeSinceLastRecievedUpdate += DeltaTime;

	//if (ClientTimeBetweenLastUpdates < KINDA_SMALL_NUMBER) // make sure numbers will be 'resonably' large 
	//	return; 
	if (MovementComponent == nullptr) // We need a movement component
	{
		UE_LOG(LogTemp, Error, TEXT("ReplicationComponent on %s has no valid MovementComponent"), *GetOwner()->GetName());
		return;
	}

	FHermiteCubicSpline Spline; // Spline

	// How much lerp should there be
	float LerpRatio = ClientTimeSinceLastRecievedUpdate / ClientTimeBetweenLastUpdates;
	// Derivative ratio converted to meters
	float VelocityToDerivative = ClientTimeBetweenLastUpdates * 100;

	CreateSpline(Spline, VelocityToDerivative);

	InterpolateLocation(Spline, LerpRatio);

	InterpolateDerivative(Spline, LerpRatio, VelocityToDerivative);

	InterpolateRotation(LerpRatio);
}

void UPlayerShipReplicationComponent::OnRep_ServerState()
{
	UE_LOG(LogTemp, Error, TEXT("ReplicationComponent on %s has recieved replicated data"), *GetOwner()->GetName());
	switch (GetOwnerRole())
	{
	case ROLE_AutonomousProxy:
		AutonomousProxy_OnRep_ServerState();
		break;
	case ROLE_SimulatedProxy:
		SimulatedProxy_OnRep_ServerState();
		break;
	default:// Ook?
		break;
	}
}

void UPlayerShipReplicationComponent::SimulatedProxy_OnRep_ServerState()
{
	ClientTimeBetweenLastUpdates = ClientTimeSinceLastRecievedUpdate;
	ClientTimeSinceLastRecievedUpdate = 0;
	UE_LOG(LogTemp, Error, TEXT("ReplicationComponent on %s has SimulatedRep"), *GetOwner()->GetName());
	ClientStartTransform = GetOwner()->GetActorTransform();
	if (MovementComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ReplicationComponent on %s has no valid MovementComponent"), *GetOwner()->GetName());
		return;
	}
	ClientStartVelocity = MovementComponent->GetVelocity();
}

void UPlayerShipReplicationComponent::AutonomousProxy_OnRep_ServerState()
{
	UE_LOG(LogTemp, Error, TEXT("ReplicationComponent on %s has AutonomusRep"), *GetOwner()->GetName());
	if (MovementComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ReplicationComponent on %s has no valid MovementComponent"), *GetOwner()->GetName());
		return;
	}
	GetOwner()->SetActorTransform(ServerState.LastMove.Transform);
	MovementComponent->SetVelocity(ServerState.LastMove.Velocity);

	ClearAcknowlegedMoves(ServerState.LastMove.TimeCreated);

	for (const FPlayerShipMove& Move : UnacknowlegedMoves)
	{
		MovementComponent->SimulateMove(Move);
	}
}

void UPlayerShipReplicationComponent::InterpolateLocation(const FHermiteCubicSpline& Spline, float LerpRatio)
{
	// Funny maths
	FVector NewLocation = Spline.InterpolateLocation(LerpRatio);
	GetOwner()->SetActorLocation(NewLocation);
}

void UPlayerShipReplicationComponent::InterpolateRotation(float LerpRatio)
{
	// Values for slerp
	FQuat TargetRotation = ServerState.LastMove.Transform.GetRotation();
	FQuat StartRotation = ClientStartTransform.GetRotation();

	// slerp to target rotation (AKA Funny maths)
	FQuat NewRotation = FQuat::Slerp(StartRotation, TargetRotation, LerpRatio);
	GetOwner()->SetActorRotation(NewRotation);
}

void UPlayerShipReplicationComponent::InterpolateDerivative(const FHermiteCubicSpline& Spline, float LerpRatio, float VelocityToDerivative)
{
	// Funny maths
	FVector NewDerivative = Spline.InterpolateDerivative(LerpRatio);
	FVector NewVelocity = NewDerivative / VelocityToDerivative;
	MovementComponent->SetVelocity(NewVelocity);
}

void UPlayerShipReplicationComponent::CreateSpline(FHermiteCubicSpline& Spline, float VelocityToDerivative)
{
	// Values for lerp interpoliation
	Spline.TargetLocation = ServerState.LastMove.Transform.GetLocation();
	Spline.StartLocation = ClientStartTransform.GetLocation();

	// Values for Hermite cube interpolation
	Spline.StartDerivative = ClientStartVelocity * VelocityToDerivative;
	Spline.TargetDerivative = ServerState.LastMove.Velocity * VelocityToDerivative;
}