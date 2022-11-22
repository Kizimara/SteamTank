// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class STEAMTANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);


	//Max force in newtones
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 20000000.f;

private:

	UTankTrack();

	virtual void BeginPlay() override;

	void DriveTrack();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplySideWaysForce();

	float CurrentThrottle;
};
