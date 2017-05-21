// Fill out your copyright notice in the Description page of Project Settings.

#include "GOTanky.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();

	if (ControlledTank && PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController > Aiming at: %s"), *PlayerTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController > Some tank is missing..."))
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	if (!GetPawn()) { return nullptr; }
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) { return nullptr; }
	ATankPlayerController* TankPlayerController = Cast<ATankPlayerController>(PlayerController);
	return TankPlayerController->GetControlledTank();
}