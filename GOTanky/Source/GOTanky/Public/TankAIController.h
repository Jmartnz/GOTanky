// Copyright Jmartnz 2017

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class GOTANKY_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Returns a pointer to the tank controlled by the player.
	ATank* GetPlayerTank() const;
	// Returns a pointer to the tank controlled by the AI.
	ATank* GetControlledTank() const;

private:
	// Maximum distance to the player that the AI tanks will try to achieve.
	float AcceptanceRadius = 3000;

};