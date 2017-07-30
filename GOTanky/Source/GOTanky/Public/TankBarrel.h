// Copyright Jmartnz 2017

#pragma once

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
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 10;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 30;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0;

};
