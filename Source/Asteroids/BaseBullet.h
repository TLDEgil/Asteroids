// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BaseBullet.generated.h"



UCLASS()
class ASTEROIDS_API ABaseBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBullet();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetData(float ArgRange, float ArgVelocity, float ArgDamage, FVector ArgInheritedVelocity, FVector ArgForwards);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	void Move(float DeltaTime);

	UPROPERTY()
		FTransform Location;

	UPROPERTY()
		float Velocity; // Speed of bullet in M/s

	UPROPERTY()
		float Range; // Range in KM before bullet gets deleted
	FVector Forwards;
	FVector InheritedVelocity; // Velocity parent had when firing the projectile

	UPROPERTY()
		float Damage; // How much damage does the bullet do on impact
};
