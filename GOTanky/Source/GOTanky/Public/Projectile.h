// Copyright Jmartnz 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class GOTANKY_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Launches the projectile at the given speed.
	void Launch(float Speed);

private:
	UProjectileMovementComponent* ProjectileMovement = nullptr;

};
