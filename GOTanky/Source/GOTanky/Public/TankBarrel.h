// Fill out your copyright notice in the Description page of Project Settings.

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
	void Elevate(float DegreesPerSecond) const;

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegree = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegree = 20;

};
