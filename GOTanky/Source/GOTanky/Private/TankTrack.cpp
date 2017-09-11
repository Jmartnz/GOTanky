// Copyright Jmartnz 2017

#include "TankTrack.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

void UTankTrack::SetThrottle(float Throttle)
{
	FVector ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	FVector TrackLocation = GetComponentLocation();
	UPrimitiveComponent* Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Tank->AddForceAtLocation(ForceApplied, TrackLocation);
}

