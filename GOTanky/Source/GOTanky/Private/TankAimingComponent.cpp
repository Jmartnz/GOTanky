// Copyright Jmartnz 2017

#include "GOTanky.h"
#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "TankTrack.h"

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
		MoveTurretTowards(AimDirection);
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%f, Solution NOT found"), TimeSeconds)
	}
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator AimDirectionAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimDirectionAsRotator - TurretRotation;
	
	// Turret always rotates on the X axis, that is Yaw
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimDirectionAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimDirectionAsRotator - BarrelRotation;

	// Barrel only elevates (rotates on the Y axis), that is Pitch
	Barrel->Elevate(DeltaRotator.Pitch);
}