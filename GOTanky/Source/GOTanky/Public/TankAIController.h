// Copyright Jmartnz 2017

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

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
	APawn* GetPlayer() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	// Maximum distance to the player that the AI tanks will try to achieve.
	float AcceptanceRadius = 7000;

};