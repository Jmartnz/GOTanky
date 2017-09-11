// Copyright Jmartnz 2017

#include "TankTurret.h"
#include "GOTanky.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewRotation = FMath::Clamp<float>(RelativeRotation.Yaw + RotationChange, MinRotationDegrees, MaxRotationDegrees);
	UE_LOG(LogTemp, Warning, TEXT("Turret rotation: %f"), RawNewRotation)
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}


