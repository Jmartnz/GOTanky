// Copyright Jmartnz 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GOTANKY_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Rotates the turret based on the relative speed.
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	// Speed at which the turret rotates in degrees per second.
	float MaxDegreesPerSecond = 30;
	UPROPERTY(EditAnywhere, Category = Setup)
	// Maximum value for the turret rotation in degrees.
	float MaxRotationDegrees = 120;
	UPROPERTY(EditAnywhere, Category = Setup)
	// Minimum value for the turret rotation in degrees.
	float MinRotationDegrees = 0;
};
