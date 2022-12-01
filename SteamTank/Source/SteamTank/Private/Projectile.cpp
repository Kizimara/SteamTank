// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "UProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement = CreateDefaultSubobject<UUProjectileMovementComponent>(FName("PT_Movement"));
	ProjectileMovement->bAutoActivate = false;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Eplosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchPT(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

void AProjectile::OnHit
(UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit
)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>()
		);

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::DestroyProjectile, DestroyDelay, false);
}

void AProjectile::DestroyProjectile()
{
	Destroy();
}