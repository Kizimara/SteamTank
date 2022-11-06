// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class STEAMTANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	void Elevate(float RelativeSpeed);

private:

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 10.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxAngleElevate = 20.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxAngleLowering = -10.f;

};
