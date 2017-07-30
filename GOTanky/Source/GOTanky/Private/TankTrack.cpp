// Fill out your copyright notice in the Description page of Project Settings.

#include "GOTanky.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	FVector ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	FVector TrackLocation = GetComponentLocation();
	UPrimitiveComponent* Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Tank->AddForceAtLocation(ForceApplied, TrackLocation);
}

