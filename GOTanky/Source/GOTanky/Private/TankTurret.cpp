// Copyright Jmartnz 2017

#include "GOTanky.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewRotation = FMath::Clamp<float>(RelativeRotation.Yaw + RotationChange, MinRotationDegrees, MaxRotationDegrees);
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}


