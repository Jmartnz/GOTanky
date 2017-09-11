// Copyright Jmartnz 2017

#include "TankAIController.h"
#include "GOTanky.h"
#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		ATank* Tank = GetPlayerTank();
		// Move towards the player
		MoveToActor(Tank, AcceptanceRadius);

		// Aim towards the player
		FVector PlayerLocation = GetPlayerTank()->GetTargetLocation();
		GetControlledTank()->AimAt(PlayerLocation);
		if (GetControlledTank()->HasFinishedReloading())
		{
			GetControlledTank()->Fire();
			GetControlledTank()->Reload();
		}
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) { return nullptr; }
	ATankPlayerController* TankPlayerController = Cast<ATankPlayerController>(PlayerController);
	return TankPlayerController->GetControlledTank();
}

ATank* ATankAIController::GetControlledTank() const
{
	if (!GetPawn()) { return nullptr; }
	return Cast<ATank>(GetPawn());
}