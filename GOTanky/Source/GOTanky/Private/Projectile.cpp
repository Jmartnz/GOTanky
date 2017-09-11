// Copyright Jmartnz 2017

#include "Projectile.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	// TODO Remember why are we using this
	ProjectileMovement->bAutoActivate = false;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::Launch(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}