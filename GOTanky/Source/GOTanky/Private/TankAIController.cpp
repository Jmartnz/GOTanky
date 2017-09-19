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
	if (ensure(GetPlayer()))
	{
		MoveToActor(GetPlayer(), AcceptanceRadius);
		FVector PlayerLocation = GetPlayer()->GetTargetLocation();
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerLocation);
		AimingComponent->Fire();
	}
}

APawn* ATankAIController::GetPlayer() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController)) { return nullptr; }
	ATankPlayerController* TankPlayerController = Cast<ATankPlayerController>(PlayerController);
	return TankPlayerController->GetPawn();
}