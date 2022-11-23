// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit
	(	UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	)
{
	DriveTrack();
	ApplySideWaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = CurrentThrottle + Throttle;
}

void UTankTrack::ApplySideWaysForce()
{
	auto TrackSlide = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	auto DeltaTime = GetWorld()->GetTimeSeconds();
	auto CorrectionAcceleration = -TrackSlide / DeltaTime * GetRightVector();
	auto Root = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (Root->GetMass() * CorrectionAcceleration) * 2; //  /2 Cause two tracks

	Root->AddForce(CorrectionForce);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplyed = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplyed, ForceLocation);
}