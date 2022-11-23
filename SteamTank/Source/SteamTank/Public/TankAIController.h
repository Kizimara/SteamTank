// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Engine.h"
#include "AIController.h"
#include "TankAIController.generated.h"


UCLASS()
class STEAMTANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptenceRadius = 8000.f;

private:

	virtual void BeginPlay() override;

	virtual void Tick(float) override;

	
	
};
