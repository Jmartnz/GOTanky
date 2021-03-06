// Copyright Jmartnz 2017

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// Log an error if the player is not controlling any tank
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Every frame we tell the tank controlled by the player to aim at the crosshair
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() const
{
	// TODO Find out why this ensure fails when opening PlayerController_BP after compile
	if (!ensure(GetPawn())) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	FVector HitLocation;
	// We only tell the tank to aim if the crosshair is hitting something
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find crosshair location in pixel coordinates
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairLocationX, ViewportSizeY * CrosshairLocationY);

	// De-project 2D coordinates position to world location
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line trace along that direction and check if it hits something
		if (GetLookVectorHitLocation(LookDirection, HitLocation))
		{
			return true;
		}
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation, // Not used
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	// Start location is the camara current location
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	// End location is the result of the following calculation
	FVector EndLocation = (StartLocation + (LookDirection * LineTraceRange));
	// TODO Remove debug line
	// DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor(255, 0, 0), false, -1.f, 0.f, 5.f);
	// Line trace using ray-casting to check if we are hitting something
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else {
		HitLocation = FVector(0);
		return false;
	}
}