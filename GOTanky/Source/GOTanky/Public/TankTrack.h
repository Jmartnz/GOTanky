// Copyright Jmartnz 2017

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force and to apply forces to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GOTANKY_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BluePrintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	// Max force per track in units
	// TODO Find a sensible default
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 30000000.0f;

};
