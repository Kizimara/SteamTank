// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


// Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;

UCLASS()
class STEAMTANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup )
	void SetBarrelReferences(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReferences(UTankTurret* TurretToSet);

protected:

	UTankAimingComponent* TankAimingComponent = nullptr;


private:

	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000.f;

};
