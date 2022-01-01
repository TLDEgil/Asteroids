// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "Asteroid.generated.h"


UCLASS()
class ASTEROIDS_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(BlueprintReadonly)
		UMeshComponent* AsteroidMesh; // The mesh of the asteroid
	
	int XRotationSpeed, YRotationSpeed, ZRotationSpeed;

	UFUNCTION()
		void RegisterHitFromBullet(float BulletDamage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere) // Amount of health this asteroid has
		float Health = 3000;
	// What is the maximum amount of health this asteroid can have
	float MaxHealth;

	UPROPERTY(EditAnywhere) // What % (as a float) of original size should this actor be on the last Health Point before it is destroyed
		float SizeAtDeathScale = .5f;

	// What scale is this asteroid at at full health
	float BaseScale = 1.0f;
	float CurrentScale;


};
