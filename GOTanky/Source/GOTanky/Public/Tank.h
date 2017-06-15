// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankTurret;
class UTankBarrel;
class AProjectile;

UCLASS()
class GOTANKY_API ATank : public APawn
{
	GENERATED_BODY()

public:	
	ATank();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	void AimAt(FVector HitLocation) const;
	bool HasFinishedReloading();

	UFUNCTION(BlueprintCallable, Category = Actions)
	void Fire() const;

	UFUNCTION(BlueprintCallable, Category = Actions)
	void Reload();

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 10000; // TODO Find sensible value

	UPROPERTY(EditAnywhere, Category = Firing)
	float ReloadDuration = 5.0f; // TODO Find sensible value

	float LastReloadTime = 0.0f; // TODO Find sensible value

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> Projectile;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
