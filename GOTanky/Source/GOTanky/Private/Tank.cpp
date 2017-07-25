// Fill out your copyright notice in the Description page of Project Settings.

#include "GOTanky.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::AimAt(FVector HitLocation) const
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

bool ATank::HasFinishedReloading()
{
	return (LastReloadTime + ReloadDuration) <= GetWorld()->GetTimeSeconds();
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetRightTrackReference(UTankTrack* TrackToSet)
{
	TankAimingComponent->SetRightTrackReference(TrackToSet);
}

void ATank::SetLeftTrackReference(UTankTrack* TrackToSet)
{
	TankAimingComponent->SetLeftTrackReference(TrackToSet);
}

void ATank::Fire()
{
	//if (HasFinishedReloading()) {
		UE_LOG(LogTemp, Warning, TEXT("%f - %s is firing!"), GetWorld()->GetTimeSeconds(), *GetName())
			auto NewProjectile = GetWorld()->SpawnActor<AProjectile>(
				Projectile,
				TankAimingComponent->GetBarrel()->GetSocketLocation(FName("Projectile")),
				TankAimingComponent->GetBarrel()->GetSocketRotation(FName("Projectile"))
				);
		NewProjectile->Launch(LaunchSpeed);
		//Reload();
	//}
}

void ATank::Reload()
{
	LastReloadTime = GetWorld()->GetTimeSeconds();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

