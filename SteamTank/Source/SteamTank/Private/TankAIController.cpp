// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("HELLO"));
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	
	
	if (!ensure(PlayerTank && ControlledTank)) { return; }

	// move toward the player
	MoveToActor(PlayerTank, AcceptenceRadius);

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	// TODO fix firing
	//ControlledTank->Fire();
	 
}