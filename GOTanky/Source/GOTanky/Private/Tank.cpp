// Copyright Jmartnz 2017

#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool ATank::HasFinishedReloading()
{
	return (LastReloadTime + ReloadDuration) <= GetWorld()->GetTimeSeconds();
}

void ATank::Fire()
{
	// We can fire only if the barrel is loaded
	if (HasFinishedReloading()) {
		auto NewProjectile = GetWorld()->SpawnActor<AProjectile>(
			Projectile,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);
		NewProjectile->Launch(LaunchSpeed);
		Reload();
	}
}

void ATank::Reload()
{
	LastReloadTime = GetWorld()->GetTimeSeconds();
}