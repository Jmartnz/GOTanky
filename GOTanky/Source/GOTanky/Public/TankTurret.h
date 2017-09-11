// Copyright Jmartnz 2017

#pragma once

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
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 30;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxRotationDegrees = 360;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinRotationDegrees = 0;
};
