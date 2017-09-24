// Copyright Jmartnz 2017

#pragma once

#include "CoreMinimal.h"
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
	// Applies a force at the track location in order to move the tank.
	void SetThrottle(float Throttle);

private:
	UPROPERTY(EditDefaultsOnly)
	// Max force per track in units.
	float MaxDrivingForce = 40000000.0f;
	float CurrentThrottle = 0.0f;

	UTankTrack();
	virtual void BeginPlay() override;
	void DriveTrack();
	void ApplySidewaysForce();

	UFUNCTION(BluePrintCallable, Category = Setup)
	void OnHit();

};
