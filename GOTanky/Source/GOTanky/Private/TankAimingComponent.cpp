// Copyright Jmartnz 2017

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "TankTrack.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UTankAimingComponent::Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

UTankBarrel* UTankAimingComponent::GetBarrel() const
{
	return Barrel;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	// TODO Remove debug line
	DrawDebugLine(GetWorld(), StartLocation, HitLocation, FColor(0, 0, 255), false, -1.f, 0.f, 5.f);
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	float TimeSeconds = GetWorld()->GetTimeSeconds();

	if(bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("AimDirection: %s"), *AimDirection.ToString())
		MoveTurretTowards(AimDirection);
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%f, Solution NOT found"), TimeSeconds)
	}
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!Turret)
	{
		UE_LOG(LogTemp, Error, TEXT("Turret could not be found..."))
		return;
	}
	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator AimDirectionAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimDirectionAsRotator - TurretRotation;
	UE_LOG(LogTemp, Warning, TEXT("Rotating turret from %f to %f"), TurretRotation.Yaw, AimDirectionAsRotator.Yaw)
	// Turret always rotates on the X axis, that is Yaw
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel) { return; }
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimDirectionAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimDirectionAsRotator - BarrelRotation;

	// Barrel only elevates (rotates on the Y axis), that is Pitch
	Barrel->Elevate(DeltaRotator.Pitch);
}