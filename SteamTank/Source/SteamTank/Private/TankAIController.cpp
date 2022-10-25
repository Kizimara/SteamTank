// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

/*ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetPawn());
}*/

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller found player: %s"), *(PlayerTank->GetName()));
	}
}



ATank* ATankAIController:: GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr;}
	
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (GetPlayerTank())
	{
		//TODO move toward the player
		
		// Aim toward at player
		  //AimAt(GetPlayerTank()->GetActorLocation());
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		// fire if we ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}