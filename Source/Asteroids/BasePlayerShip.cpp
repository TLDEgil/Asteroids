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
	WeaponSystem			= CreateDefaultSubobject<UBasePlayerShipGun>(TEXT("Weapon Component"));

	// Check if all the subcomponents were created properly
	if (!MovementComponent)		UE_LOG(LogTemp, Error, TEXT("Failed to create MovementComponent on %s"), *GetName());
	if (!ReplicationComponent)	UE_LOG(LogTemp, Error, TEXT("Failed to create ReplicationComponent on %s"), *GetName());
	if (!EngineComponent)		UE_LOG(LogTemp, Error, TEXT("Failed to create EngineComponent on %s"), *GetName());
	if (!WeaponSystem)			UE_LOG(LogTemp, Error, TEXT("Failed to create WeaponSystem on %s"), *GetName());
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
	PlayerInputComponent->BindAxis("PitchAxisInput", this, &ABasePlayerShip::SetPitchAxis);
	PlayerInputComponent->BindAxis("YawAxisInput", this, &ABasePlayerShip::SetYawAxis);
	PlayerInputComponent->BindAxis("RollAxisInput", this, &ABasePlayerShip::SetRollAxis);
	PlayerInputComponent->BindAxis("ThrustAxisInput", this, &ABasePlayerShip::SetTargetThrust);
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
	if (!EngineComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid EngineComponent on %s"), * GetName());
		return 0.0f;
	}
	return EngineComponent->GetThrust();
}

void ABasePlayerShip::SetTargetThrust(float NewThrust)
{
	if (!EngineComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid EngineComponent on %s"), *GetName());
		return;
	}
	EngineComponent->SetTargetThrust(NewThrust);
}

float ABasePlayerShip::GetMaxThrust() const
{
	if (!EngineComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid EngineComponent on %s"), *GetName());
		return 0.0f;
	}
	return EngineComponent->GetMaxThrust();
}

void ABasePlayerShip::SetMaxThrust(float NewMaxThrust)
{
	if (!EngineComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid EngineComponent on %s"), *GetName());
		return;
	}
	EngineComponent->SetMaxThrust(NewMaxThrust);
}

float ABasePlayerShip::GetThrustChangeSpeed() const
{
	if (!EngineComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid EngineComponent on %s"), *GetName());
		return 0.0f;
	}
	return EngineComponent->GetThrustChangeSpeed();
}

void ABasePlayerShip::SetThrustChangeSpeed(float NewThrustChangeSpeed)
{
	if (!EngineComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid EngineComponent on %s"), *GetName());
		return;
	}
	EngineComponent->SetThrustChangeSpeed(NewThrustChangeSpeed);
}

int ABasePlayerShip::GetRateOfFire()
{
	if (!WeaponSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid WeaponSystem on %s"), *GetName());
		return 0;
	}
	return WeaponSystem->GetRateOfFire();
}

void ABasePlayerShip::SetRateOfFire(int NewRateOfFire)
{
	if (!WeaponSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid WeaponSystem on %s"), *GetName());
		return;
	}
	WeaponSystem->SetRateOfFire(NewRateOfFire);
}

float ABasePlayerShip::GetBulletVelocity()
{
	if (!WeaponSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid WeaponSystem on %s"), *GetName());
		return 0.0f;
	}
	return WeaponSystem->GetBulletVelocity();
}

void ABasePlayerShip::SetBulletVelocity(float NewBulletVelocity)
{
	if (!WeaponSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid WeaponSystem on %s"), *GetName());
		return;
	}
	WeaponSystem->SetBulletVelocity(NewBulletVelocity);
}

float ABasePlayerShip::GetBulletDamage()
{
	if (!WeaponSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid WeaponSystem on %s"), *GetName());
		return 0.0f;
	}
	return WeaponSystem->GetBulletDamage();
}

void ABasePlayerShip::SetBulletDamage(float NewBulletDamage)
{
	if (!WeaponSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid WeaponSystem on %s"), *GetName());
		return;
	}
	WeaponSystem->SetBulletDamage(NewBulletDamage);
}

float ABasePlayerShip::GetBulletRange()
{
	if (!WeaponSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid WeaponSystem on %s"), *GetName());
		return 0.0f;
	}
	return WeaponSystem->GetBulletRange();
}

void ABasePlayerShip::SetBulletRange(float NewBulletRange)
{
	if (!WeaponSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid WeaponSystem on %s"), *GetName());
		return;
	}
	WeaponSystem->SetBulletRange(NewBulletRange);
}

void ABasePlayerShip::SetPitchAxis(float PitchAxis)
{
	if (!MovementComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid MovementComponent on %s"), *GetName());
		return;
	}
	MovementComponent->SetPitch(PitchAxis);
}

void ABasePlayerShip::SetYawAxis(float YawAxis)
{
	if (!MovementComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid MovementComponent on %s"), *GetName());
		return;
	}
	MovementComponent->SetYaw(YawAxis);
}

void ABasePlayerShip::SetRollAxis(float RollAxis)
{
	if (!MovementComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid MovementComponent on %s"), *GetName());
		return;
	}
	MovementComponent->SetRoll(RollAxis);
}
