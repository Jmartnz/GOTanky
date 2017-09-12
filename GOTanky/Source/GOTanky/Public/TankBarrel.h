// Copyright Jmartnz 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GOTANKY_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Elevates the barrel based on the relative speed.
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	// Speed at which the barrel elevates in degrees per second.
	float MaxDegreesPerSecond = 10;
	UPROPERTY(EditAnywhere, Category = Setup)
	// Maximum value for the barrel elevation in degrees.
	float MaxElevationDegrees = 30;
	UPROPERTY(EditAnywhere, Category = Setup)
	// Minimum value for the barrel elevation in degrees.
	float MinElevationDegrees = 0;
};
