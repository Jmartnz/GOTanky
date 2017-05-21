// Fill out your copyright notice in the Description page of Project Settings.

#include "GOTanky.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController > My Tank is: %s"), *ControlledTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController is not controlling any Tank..."))
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}