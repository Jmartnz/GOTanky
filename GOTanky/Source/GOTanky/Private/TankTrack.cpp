// Copyright Jmartnz 2017

#include "TankTrack.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	
}

void UTankTrack::ApplySidewaysForce()
{
	// Calculate SlippageSpeed
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// Get AccelerationCorrection to apply at this frame
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector AccelerationCorrection = -SlippageSpeed / DeltaTime * GetRightVector();
	// Get Tank root component
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	// Calculate CorrectionForce
	FVector CorrectionForce = (TankRoot->GetMass() * AccelerationCorrection) / 2;
	// Apply force to correct sideways movement
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::OnHit()
{
	DriveTrack();
	ApplySidewaysForce();
	UE_LOG(LogTemp, Warning, TEXT("%s : %f"), *GetName(), CurrentThrottle)
	CurrentThrottle = 0.0f;
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
	FVector TrackLocation = GetComponentLocation();
	UPrimitiveComponent* Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Tank->AddForceAtLocation(ForceApplied, TrackLocation);
}

