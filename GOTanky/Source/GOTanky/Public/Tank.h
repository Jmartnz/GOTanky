// Copyright Jmartnz 2017

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovementComponent;
class UTankTurret;
class UTankBarrel;
class UTankTrack;
class AProjectile;

UCLASS()
class GOTANKY_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Tell the TankAimingComponent to aim at this location.
	void AimAt(FVector HitLocation) const;
	// Returns true if the tank has finished reloading.
	bool HasFinishedReloading();

	UFUNCTION(BlueprintCallable, Category = Actions)
	// Spawns a new projectile at barrel location and fires it.
	void Fire();
	UFUNCTION(BlueprintCallable, Category = Actions)
	// Reloads the barrel in order to fire again.
	void Reload();

protected:
	UPROPERTY(BluePrintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(BluePrintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 10000; // TODO Find sensible value
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadDuration = 5.0f; // TODO Find sensible value
	float LastReloadTime = 0.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> Projectile;

	// Called to bind functionality to input.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
