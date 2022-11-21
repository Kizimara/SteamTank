// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	auto TrackSlide = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	auto CorrectionAcceleration = -TrackSlide / DeltaTime * GetRightVector();

	auto Root = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto CorrectionForce = (Root->GetMass() * CorrectionAcceleration)/2; // Cause two tracks

	Root->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplyed = GetForwardVector() * Throttle * MaxDrivingForce;

	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplyed,ForceLocation);

	
}