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
	// TODO Remember why this is necessary
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATank::AimAt(FVector HitLocation) const
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
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
			TankAimingComponent->GetBarrel()->GetSocketLocation(FName("Projectile")),
			TankAimingComponent->GetBarrel()->GetSocketRotation(FName("Projectile"))
		);
		NewProjectile->Launch(LaunchSpeed);
		Reload();
	}
}

void ATank::Reload()
{
	LastReloadTime = GetWorld()->GetTimeSeconds();
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}