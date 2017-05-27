// Fill out your copyright notice in the Description page of Project Settings.

#include "GOTanky.h"
#include "TankAimingComponent.h"

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if(bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		// UE_LOG(LogTemp, Warning, TEXT("%s > firing at: %s"), *GetOwner()->GetName(), *AimDirection.ToString())
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// TODO
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimDirectionAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimDirectionAsRotator - BarrelRotation;
	UE_LOG(LogTemp, Warning, TEXT("%s > DeltaRotator: %s"), *GetOwner()->GetName(), *DeltaRotator.ToString())
}

UFUNCTION(BlueprintCallable, Category = Setup)
void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}