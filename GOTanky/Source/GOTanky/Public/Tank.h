// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;

UCLASS()
class GOTANKY_API ATank : public APawn
{
	GENERATED_BODY()

public:	
	ATank();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void AimAt(FVector HitLocation) const;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 10000; // TODO Find sensible value

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
