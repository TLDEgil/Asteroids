// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerShip.h"
#include "Components/InputComponent.h"
#include "Engine/World.H"
#include "Net/UnrealNetwork.h"

// Sets default values
ABasePlayerShip::ABasePlayerShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent		= CreateDefaultSubobject<UPlayerShipMovementComponent>(TEXT("Movement Component"));
	ReplicationComponent	= CreateDefaultSubobject<UPlayerShipReplicationComponent>(TEXT("Replication Component"));
	EngineComponent			= CreateDefaultSubobject<UPlayerShipEngineComponent>(TEXT("Engine Compoennt"));

	// Check if all the subcomponents were created properly
	if (!MovementComponent)		UE_LOG(LogTemp, Error, TEXT("Failed to create MovementComponent on %s"), *GetName());
	if (!ReplicationComponent)	UE_LOG(LogTemp, Error, TEXT("Failed to create ReplicationComponent on %s"), *GetName());
	if (!EngineComponent)		UE_LOG(LogTemp, Error, TEXT("Failed to create EngineComponent on %s"), *GetName());
}

// Called when the game starts or when spawned
void ABasePlayerShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABasePlayerShip::GetBaseMass() const
{
	return BaseMass;
}

void ABasePlayerShip::SetBaseMass(float NewBaseMass)
{
	BaseMass = NewBaseMass;
}

float ABasePlayerShip::GetThrust() const
{
	return EngineComponent->GetThrust();
}

void ABasePlayerShip::SetThrust(float NewThrust)
{
	EngineComponent->SetTargetThrust(NewThrust);
}

float ABasePlayerShip::GetMaxThrust() const
{
	return EngineComponent->GetMaxThrust();
}

void ABasePlayerShip::SetMaxThrust(float NewMaxThrust)
{
	EngineComponent->SetMaxThrust(NewMaxThrust);
}

float ABasePlayerShip::GetThrustChangeSpeed() const
{
	return EngineComponent->GetThrustChangeSpeed();
}

void ABasePlayerShip::SetThrustChangeSpeed(float NewThrustChangeSpeed)
{
	EngineComponent->SetThrustChangeSpeed(NewThrustChangeSpeed);
}

