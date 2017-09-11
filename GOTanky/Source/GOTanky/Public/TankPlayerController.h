// Copyright Jmartnz 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class GOTANKY_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	// Return the tank controlled by the player.
	ATank* GetControlledTank() const;

	// Tell the controlled tank to aim at the crosshair.
	void AimTowardsCrosshair() const;
	
private:
	UPROPERTY(EditAnywhere)
	// Horizontal location of the crosshair.
	float CrosshairLocationX = 0.5f;
	UPROPERTY(EditAnywhere)
	// Vertical location of the crosshair.
	float CrosshairLocationY = 0.3333f;
	UPROPERTY(EditAnywhere)
	// Line trace maximum range used to calculate HitLocation.
	float LineTraceRange = 10000.0f;

	// Check if the crosshair is aiming at something that could be hit. Returns true if so.
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	// Given crosshair coordinates in 2D, calculates its LookDirection in the 3D World. Returns false if impossible to determine value.
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	// Calculates the HitLocation using the camara current location, the LookDirection and the LineTraceRange.
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
