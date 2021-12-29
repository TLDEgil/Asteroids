// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShipMovementComponent.h"
#include "BasePlayerShip.h"

// Sets default values for this component's properties
UPlayerShipMovementComponent::UPlayerShipMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UPlayerShipMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	EngineComponent = GetOwner()->FindComponentByClass<UPlayerShipEngineComponent>();

	if (!EngineComponent)
	{
		PrimaryComponentTick.bCanEverTick = false;
		UE_LOG(LogTemp, Error, TEXT("MovementComponent on %s could not find an EngineComponent"), *GetOwner()->GetName());
	}
}

// Called every frame
void UPlayerShipMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateValues(DeltaTime);
	LastMove = CreateMove(DeltaTime);
	SimulateMove(LastMove);
	ApplyMovement(LastMove);
	ApplyRotation(LastMove);
}

void UPlayerShipMovementComponent::UpdateValues(float DeltaTime)
{
	if (Pitch) CurrentPitchRate += Pitch * PitchRateIncrease * DeltaTime;
	else
	{
		if (CurrentPitchRate > 0) CurrentPitchRate -= PitchRateIncrease * DeltaTime;
		else CurrentPitchRate += PitchRateIncrease * DeltaTime;
		
		if (fabs(CurrentPitchRate) < (PitchRateIncrease*DeltaTime) + KINDA_SMALL_NUMBER) CurrentPitchRate = 0.0f;
	}

	if (Yaw) CurrentYawRate += Yaw * YawRateIncrease * DeltaTime;
	else
	{
		if (CurrentYawRate > 0) CurrentYawRate -= YawRateIncrease * DeltaTime;
		else CurrentYawRate += YawRateIncrease * DeltaTime;

		if (fabs(CurrentYawRate) < (YawRateIncrease * DeltaTime) + KINDA_SMALL_NUMBER) CurrentYawRate = 0.0f;
	}

	if (Roll) CurrentRollRate += Roll * RollRateIncrease * DeltaTime;
	else
	{
		if (CurrentRollRate > 0) CurrentRollRate -= RollRateIncrease * DeltaTime;
		else CurrentRollRate += RollRateIncrease * DeltaTime;

		if (fabs(CurrentRollRate) < (RollRateIncrease * DeltaTime) + KINDA_SMALL_NUMBER) CurrentRollRate = 0.0f;
	}
}

FPlayerShipMove UPlayerShipMovementComponent::GetLastMove()
{
	return LastMove;
}

FPlayerShipMove UPlayerShipMovementComponent::CreateMove(float DeltaTime)
{
	FPlayerShipMove Move;
	Move.TimeCreated = GetOwner()->GetWorld()->TimeSeconds;
	Move.DeltaTime = DeltaTime;
	Move.Location = GetOwner()->GetTransform();
	Move.PitchRate = CurrentPitchRate;
	Move.YawRate = CurrentYawRate;
	Move.RollRate = CurrentRollRate ;
	Move.Throttle = Throttle;
	return Move;
}

void UPlayerShipMovementComponent::SimulateMove(const FPlayerShipMove& Move)
{
	//UE_LOG(LogTemp, Warning, TEXT("Engine Thrust: %f"), EngineComponent->GetThrust());
	FVector AppliedForce = GetOwner()->GetActorForwardVector() * EngineComponent->GetThrust();
	FVector Acceleration = AppliedForce / Cast<ABasePlayerShip>(GetOwner())->GetBaseMass();
	Velocity += Acceleration * Move.DeltaTime;
	ApplyRotation(Move);
	ApplyMovement(Move);
}

void UPlayerShipMovementComponent::ApplyMovement(const FPlayerShipMove& Move)
{
	FVector Translation = Velocity * Move.DeltaTime * 100;
	Translation = Translation.GetClampedToMaxSize(MaxSpeed);
	UE_LOG(LogTemp, Warning, TEXT("Current Ship Speed: %f"), Translation.Size());
	FHitResult Hit;
	GetOwner()->AddActorWorldOffset(Translation, true, &Hit);

	if (Hit.IsValidBlockingHit())
	{
		Velocity = FVector(0);
	}
}

// F quaternions
void UPlayerShipMovementComponent::ApplyRotation(const FPlayerShipMove& Move)
{
	// Get the angles of rotation
	float PitchRotationAngle	= CurrentPitchRate	* Move.DeltaTime;
	float YawRotationAngle		= CurrentYawRate	* Move.DeltaTime;
	float RollRotationAngle		= CurrentRollRate	* Move.DeltaTime;

	// Figure this out yourself. My head hurts too much now.
	FQuat PitchRotationDelta(GetOwner()->GetActorRightVector(),	FMath::DegreesToRadians(PitchRotationAngle));
	FQuat YawRotationDelta(GetOwner()->GetActorUpVector(),		FMath::DegreesToRadians(YawRotationAngle));
	FQuat RollRotationDelta(GetOwner()->GetActorForwardVector(),FMath::DegreesToRadians(RollRotationAngle));

	// Apply the hard won quats to rotation
	GetOwner()->AddActorWorldRotation(PitchRotationDelta);
	GetOwner()->AddActorWorldRotation(YawRotationDelta);
	GetOwner()->AddActorWorldRotation(RollRotationDelta);
}

FVector UPlayerShipMovementComponent::GetVelocity() const
{
	return Velocity;
}

void UPlayerShipMovementComponent::SetVelocity(FVector NewVelocity)
{
	Velocity = NewVelocity;
}

float UPlayerShipMovementComponent::GetThrottle() const
{
	return Throttle;
}

void UPlayerShipMovementComponent::SetThrottle(float NewThrottle)
{
	Throttle = NewThrottle;
}

float UPlayerShipMovementComponent::GetPitch() const
{
	return Pitch;
}

void UPlayerShipMovementComponent::SetPitch(float NewPitch)
{
	Pitch = NewPitch;
}

float UPlayerShipMovementComponent::GetYaw() const
{
	return Yaw;
}

void UPlayerShipMovementComponent::SetYaw(float NewYaw)
{
	Yaw = NewYaw;
}

float UPlayerShipMovementComponent::GetRoll() const
{
	return Roll;
}

void UPlayerShipMovementComponent::SetRoll(float NewRoll)
{
	Roll = NewRoll;
}