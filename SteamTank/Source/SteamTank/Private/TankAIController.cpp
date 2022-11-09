// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "Tank.h"
#include "TankAIController.h"

/*ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetPawn());
}*/

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank)
	{
		//TODO move toward the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();  // TODO make limit fire rate
	}
}