// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class STEAMTANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	virtual float TakeDamage(
		float Damage,
		FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPersent() const;

	FTankDelegate OnDeath;

private:

	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
