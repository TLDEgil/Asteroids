// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerShipEngineComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDS_API UPlayerShipEngineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerShipEngineComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetThrust() const;
	void SetThrust(float NewThrust);

	float GetTargetThrust() const;
	void SetTargetThrust(float NewTargetThrust);

	float GetMaxThrust() const;
	void SetMaxThrust(float NewMaxThrust);

	float GetThrustChangeSpeed() const;
	void SetThrustChangeSpeed(float NewThrustChangeSpeed);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere)
		float CurrentThrust; // How much thrust is currently being produced in Newtons
	UPROPERTY(EditAnywhere)
		float MaxThrust = 150000; // Maximum thrust that can be produced in Newtons
	UPROPERTY(EditAnywhere)
		float ThrustChangeSpeed = 10000; // How much can the thrust change in one second
	UPROPERTY(EditAnywhere)
		float TargetThrust; // What is the trust we want to output

	UFUNCTION()
		void UpdateThrustOutput(float DeltaTime);
};