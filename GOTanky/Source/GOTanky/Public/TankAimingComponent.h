// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; // forward declaration

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GOTANKY_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTankAimingComponent();
	void AimAt(FVector HitLocation, float LaunchSpeed);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

private:
	UTankBarrel* Barrel = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
};
