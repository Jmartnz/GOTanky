// Fill out your copyright notice in the Description page of Project Settings.

#include "GOTanky.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController > My Tank is: %s"), *ControlledTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController is not controlling any Tank..."))
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}