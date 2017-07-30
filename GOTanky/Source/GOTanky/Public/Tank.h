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

	void AimAt(FVector HitLocation) const;
	bool HasFinishedReloading();

	UFUNCTION(BlueprintCallable, Category = Actions)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Actions)
	void Reload();

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 10000; // TODO Find sensible value

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadDuration = 5.0f; // TODO Find sensible value

	float LastReloadTime = 0.0f; // TODO Find sensible value

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> Projectile;

protected:
	UPROPERTY(BluePrintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BluePrintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
