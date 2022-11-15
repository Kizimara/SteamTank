// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankName = GetOwner()->GetName();
	auto TankVelocity = MoveVelocity.ToString();

	UE_LOG(LogTemp, Warning, TEXT("%s Tank, move velocity is %s "), *TankName , *TankVelocity );
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) {
		UE_LOG(LogTemp, Warning, TEXT("items were not received"));
		return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) {return;}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}


