// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankTurret;
class UTankBarrel;
class UTankTrack;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GOTANKY_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTankAimingComponent();
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetRightTrackReference(UTankTrack* TrackToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetLeftTrackReference(UTankTrack* TrackToSet);
	UTankBarrel* GetBarrel() const;
	void AimAt(FVector HitLocation, float LaunchSpeed);

private:
	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;
	UTankTrack* RightTrack = nullptr;
	UTankTrack* LeftTrack = nullptr;
	void MoveTurretTowards(FVector AimDirection);
	void MoveBarrelTowards(FVector AimDirection);
};
