// Copyright Jmartnz 2017

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading
};

class UTankTurret;
class UTankBarrel;
class UTankTrack;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GOTANKY_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	UTankBarrel* GetBarrel() const;
	void AimAt(FVector HitLocation, float LaunchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;
	UTankTrack* RightTrack = nullptr;
	UTankTrack* LeftTrack = nullptr;
	void MoveTurretTowards(FVector AimDirection);
	void MoveBarrelTowards(FVector AimDirection);
};
