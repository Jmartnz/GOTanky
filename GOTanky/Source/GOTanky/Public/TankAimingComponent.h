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
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	// Initialise the Turret and the Barrel for aiming use.
	void Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Actions)
	// Spawns a new projectile at barrel location and fires it.
	void Fire();
	UFUNCTION(BlueprintCallable, Category = Actions)
	// Reloads the barrel in order to fire again.
	void Reload();

	// Calculates the aim solution then tells the Turret and the Barrel to aim at resulting direction.
	void AimAt(FVector HitLocation);
	// Handles reload logic and sets FiringState accordingly.
	void SetFiringState();

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	// Enum which dictates the current firing state of the Barrel.
	EFiringState FiringState = EFiringState::Aiming;
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 5000; // TODO Find sensible value

private:
	UTankAimingComponent();
	// TODO Move explosion sound to Projectile
	UPROPERTY(EditAnywhere, Category = Firing)
	USoundBase* ExplosionSound = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadDuration = 2.5f; // TODO Find sensible value
	float LastReloadTime = 0.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> Projectile;
	FVector AimDirection = FVector(0);

	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;

	// Returns true if the tank has finished reloading.
	bool HasFinishedReloading();
	// Returns true if the barrel is locked and ready to fire.
	bool IsBarrelLocked();
	// Moves the turret towards the AimDirection by rotating its X axis.
	void MoveTurretTowards();
	// Moves the Barrel towards the AimDirection by rotating its Y axis.
	void MoveBarrelTowards();

};
