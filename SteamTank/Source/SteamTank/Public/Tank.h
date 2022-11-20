// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


// Forward Declarations
class UTankBarrel;
class AProjectile;

UCLASS()
class STEAMTANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void Fire();

private:

	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "setup")
	TSubclassOf<AProjectile> ProjectileBP;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.f;

	UTankBarrel* Barrel = nullptr;

	double LastFireTime = 0;
};
