// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


// Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankTrack;
class UTankAimingComponent;

UCLASS()
class STEAMTANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	

	UFUNCTION(BlueprintCallable, Category = Setup )
	void SetBarrelReferences(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReferences(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTrackReferences(UTankTrack* TrackToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();


	void AimAt(FVector HitLocation);

protected:

	UTankAimingComponent* TankAimingComponent = nullptr;


private:

	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = setup)
	TSubclassOf<AProjectile> ProjectileBP;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 8000.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.f;

	UTankBarrel* Barrel = nullptr;

	double LastFireTime = 0;
};
