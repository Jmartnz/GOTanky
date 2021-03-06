// Copyright Jmartnz 2017

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	UpdateFiringState();
}

void UTankAimingComponent::Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::UpdateFiringState()
{
	if (HasAmmo())
	{
		if (HasFinishedReloading())
		{
			if (IsBarrelLocked())
			{
				FiringState = EFiringState::Locked;
			}
			else
			{
				FiringState = EFiringState::Aiming;
			}
		}
		else
		{
			FiringState = EFiringState::Reloading;
		}
	}
	else
	{
		FiringState = EFiringState::OutOfAmmo;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UTankAimingComponent::HasAmmo() const
{
	return Ammo > 0;
}

bool UTankAimingComponent::HasFinishedReloading()
{
	return (LastReloadTime + ReloadDuration) <= GetWorld()->GetTimeSeconds();
}

bool UTankAimingComponent::IsBarrelLocked()
{
	if (!ensure(Barrel)) { return false; }
	return Barrel->GetForwardVector().Equals(AimDirection, 0.05f);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel) || !ensure(Projectile)) { return; }
	// We can fire only if the barrel is locked
	if (FiringState == EFiringState::Locked) {
		auto NewProjectile = GetWorld()->SpawnActor<AProjectile>(
			Projectile,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		NewProjectile->Launch(LaunchSpeed);
		if (ExplosionSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, Barrel->GetSocketLocation(FName("Projectile")));
		}
		if (Ammo > 0)
		{
			Ammo--;
		}
		Reload();
	}
}

void UTankAimingComponent::Reload()
{
	LastReloadTime = GetWorld()->GetTimeSeconds();
	FiringState = EFiringState::Reloading;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Turret) || !ensure(Barrel)) { return; }
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector OutLaunchVelocity;
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

	if(bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveTurretTowards();
		MoveBarrelTowards();
	}
	else
	{
		// TODO Add behavior when no solution is found
	}
}

void UTankAimingComponent::MoveTurretTowards()
{
	if (!ensure(Turret)) { return; }
	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator AimDirectionAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimDirectionAsRotator - TurretRotation;
	// Turret always rotates on the X axis, that is Yaw
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	
}

void UTankAimingComponent::MoveBarrelTowards()
{
	if (!ensure(Barrel)) { return; }
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimDirectionAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimDirectionAsRotator - BarrelRotation;
	// Barrel only elevates (rotates on the Y axis), that is Pitch
	Barrel->Elevate(DeltaRotator.Pitch);
}