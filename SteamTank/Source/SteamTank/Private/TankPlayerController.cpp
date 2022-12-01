// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"





void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	//if (!ensure(AimingComponent)) { return; }
	//	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OutControll);
	}
}

void ATankPlayerController::OutControll()
{
	StartSpectatingOnly();
}



void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimCrosshair();
}


void ATankPlayerController::AimCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);

	FVector HitLocation; // out param
	
	if(GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewPortSizeX, ViewPortSizeY;

	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);

	FVector LookDirection;

	if(GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line Trace along that LookDirection, and see what we hit
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // temp solution

	return DeprojectScreenPositionToWorld
	(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if(GetWorld()->LineTraceSingleByChannel
		(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
		{
		HitLocation = HitResult.Location;
			return true;
		}
	else
	{
		return false;
	}
		
}