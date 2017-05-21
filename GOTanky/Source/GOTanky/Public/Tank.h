// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class GOTANKY_API ATank : public APawn
{
	GENERATED_BODY()

public:	
	ATank();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void AimAt(FVector HitLocation) const;

private:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
