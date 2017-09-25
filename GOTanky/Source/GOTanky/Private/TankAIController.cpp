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
		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();
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