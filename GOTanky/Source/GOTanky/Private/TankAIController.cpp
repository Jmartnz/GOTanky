// Fill out your copyright notice in the Description page of Project Settings.

#include "GOTanky.h"
#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		// TODO Move towards the player

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