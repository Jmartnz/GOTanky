// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	void AimTowardsCrosshair() const;
	ATank* GetControlledTank() const;
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

private:
	// Attributes
	UPROPERTY(EditAnywhere)
	float CrosshairLocationX = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrosshairLocationY = 0.3333f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 10000.0f;
};
