// Copyright Jmartnz 2017

#pragma once

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

	ATank* GetPlayerTank() const;
	ATank* GetControlledTank() const;

private:
	float AcceptanceRadius = 3000;
};