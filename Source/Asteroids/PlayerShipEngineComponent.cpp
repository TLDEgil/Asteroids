// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerShipEngineComponent.h"

#include "Math.h"



// Sets default values for this component's properties
UPlayerShipEngineComponent::UPlayerShipEngineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerShipEngineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPlayerShipEngineComponent::UpdateThrustOutput(float DeltaTime)
{	
	UE_LOG(LogTemp, Warning, TEXT("CurrentThrust: %f \tTargetThrust: %f"), CurrentThrust, TargetThrust);
	if(DeltaTime < KINDA_SMALL_NUMBER) return; // Checking to quickly

	// If close enough to target thrust, skip all the calculations
	float ThrustChange = ThrustChangeSpeed * DeltaTime; // How much will thrust change this tick
	if (fabs(CurrentThrust - TargetThrust) < ThrustChange)
	{
		CurrentThrust = TargetThrust;
		return;
	}
	

	// Check for increase or decrease of thrust
	
	if (CurrentThrust < TargetThrust)
	{	// Increase output thrust
		CurrentThrust += ThrustChange;
		// Ensure Thrust is still in valid range
		if (CurrentThrust > MaxThrust)
			CurrentThrust = MaxThrust;
	}
	else
	{	// Decrease thrust
		CurrentThrust -= ThrustChange;
		if (CurrentThrust < -MaxThrust)
			CurrentThrust = -MaxThrust;
	}
	
}


// Called every frame
void UPlayerShipEngineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateThrustOutput(DeltaTime);
}

float UPlayerShipEngineComponent::GetThrust() const
{
	return CurrentThrust;
}

void UPlayerShipEngineComponent::SetThrust(float NewThrust)
{
	CurrentThrust = NewThrust;
}

float UPlayerShipEngineComponent::GetTargetThrust() const
{
	return TargetThrust;
}

void UPlayerShipEngineComponent::SetTargetThrust(float NewTargetThrust)
{
	TargetThrust = NewTargetThrust;
}

float UPlayerShipEngineComponent::GetMaxThrust() const
{
	return MaxThrust;
}

void UPlayerShipEngineComponent::SetMaxThrust(float NewMaxThrust)
{
	MaxThrust = NewMaxThrust;
}

float UPlayerShipEngineComponent::GetThrustChangeSpeed() const
{
	return ThrustChangeSpeed;
}

void UPlayerShipEngineComponent::SetThrustChangeSpeed(float NewThrustChangeSpeed)
{
	ThrustChangeSpeed = NewThrustChangeSpeed;
}
