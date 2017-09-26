// Copyright Jmartnz 2017

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayer())
	{
		MoveToActor(GetPlayer(), AcceptanceRadius);
		FVector PlayerLocation = GetPlayer()->GetTargetLocation();

		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerLocation);
		AimingComponent->UpdateFiringState();
		switch (AimingComponent->GetFiringState())
		{
			case EFiringState::Locked:
				AimingComponent->Fire();
				// UE_LOG(LogTemp, Warning, TEXT("AI Tank %s FIRE!"), *GetName())
				break;
			case EFiringState::Aiming:
				// UE_LOG(LogTemp, Warning, TEXT("AI Tank %s is aiming..."), *GetName())
				break;
			case EFiringState::Reloading:
				// UE_LOG(LogTemp, Warning, TEXT("AI Tank %s is reloading!"), *GetName())
				break;
			case EFiringState::OutOfAmmo:
				// UE_LOG(LogTemp, Warning, TEXT("AI Tank %s is out of ammo."), *GetName())
				break;
		}
	}
}

APawn* ATankAIController::GetPlayer() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) { return nullptr; }
	ATankPlayerController* TankPlayerController = Cast<ATankPlayerController>(PlayerController);
	return TankPlayerController->GetPawn();
}