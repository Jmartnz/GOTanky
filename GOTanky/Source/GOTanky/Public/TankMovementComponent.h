// Copyright Jmartnz 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible of driving the tank tracks.
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class GOTANKY_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveBackwards(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnLeft(float Throw);

private:
	UTankTrack* RightTrack = nullptr;
	UTankTrack* LeftTrack = nullptr;

	// Called from the pathfinding logic by the AI Controller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed);

};
