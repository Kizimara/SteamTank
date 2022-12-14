// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto SkylarForForward = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(SkylarForForward);

	auto ProductForTurn = FVector::CrossProduct(AIForwardIntention,TankForward).Z;
	IntendTurnRight(ProductForTurn);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return;}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}


