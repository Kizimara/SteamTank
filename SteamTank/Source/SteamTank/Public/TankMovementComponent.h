// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STEAMTANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);

	
private:

	//This function called from (MoveToActor) at AI controller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
