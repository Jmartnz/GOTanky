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
		// Move towards the player within the acceptance radius
		MoveToActor(GetPlayer(), AcceptanceRadius);
		// Aim towards the player
		FVector PlayerLocation = GetPlayer()->GetTargetLocation();
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerLocation);
		// Fire when the barrel is loaded
		/*if (GetControlledTank()->HasFinishedReloading())
		{
			GetControlledTank()->Fire();
			GetControlledTank()->Reload();
		}*/
	}
}

APawn* ATankAIController::GetPlayer() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) { return nullptr; }
	ATankPlayerController* TankPlayerController = Cast<ATankPlayerController>(PlayerController);
	return TankPlayerController->GetPawn();
}