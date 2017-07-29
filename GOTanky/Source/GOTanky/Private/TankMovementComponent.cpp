// Fill out your copyright notice in the Description page of Project Settings.

#include "GOTanky.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet)
{
	RightTrack = RightTrackToSet;
	LeftTrack = LeftTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!RightTrack || !LeftTrack) { return; }
	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!RightTrack || !LeftTrack) { return; }
	RightTrack->SetThrottle(-Throw);
	LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);
}