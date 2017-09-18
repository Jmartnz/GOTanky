// Copyright Jmartnz 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Locked,		// The Barrel is not moving and is ready to fire.
	Aiming,		// The Barrel is moving and therefore it cannot fire.
	Reloading	// The Tank is reloading and therefore it cannot fire.
};

class UTankTurret;
class UTankBarrel;
class AProjectile;

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GOTANKY_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	// Initialise the Turret and the Barrel for aiming use.
	void Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Actions)
	// Spawns a new projectile at barrel location and fires it.
	void Fire();
	UFUNCTION(BlueprintCallable, Category = Actions)
	// Reloads the barrel in order to fire again.
	void Reload();

	// Returns true if the tank has finished reloading.
	bool HasFinishedReloading();
	// Calculates the aim solution then tells the Turret and the Barrel to aim at resulting direction.
	void AimAt(FVector HitLocation);
	// Returns a pointer to Barrel used by the aiming component.
	UTankBarrel* GetBarrel() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	// Enum which dictates the current firing state of the Barrel.
	EFiringState FiringState = EFiringState::Locked;
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 10000; // TODO Find sensible value

private:
	UTankAimingComponent();

	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;

	// Moves the turret towards the AimDirection by rotating its X axis.
	void MoveTurretTowards(FVector AimDirection);
	// Moves the Barrel towards the AimDirection by rotating its Y axis.
	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadDuration = 1.0f; // TODO Find sensible value
	float LastReloadTime = 0.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> Projectile;
};
