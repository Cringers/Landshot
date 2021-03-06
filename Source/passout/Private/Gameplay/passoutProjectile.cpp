// Copyright Epic Games, Inc. All Rights Reserved.

#include "Gameplay/passoutProjectile.h"
#include "Gameplay/passoutCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "VoxelTools/Gen/VoxelSphereTools.h"
#include "VoxelWorld.h"

ApassoutProjectile::ApassoutProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ApassoutProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	SetReplicates(true);
	SetReplicateMovement(true);
}


void ApassoutProjectile::removeSphereOnHit_Implementation(AVoxelWorld* world, const FHitResult& Hit)
{
   	UVoxelSphereTools::RemoveSphere(world, Hit.ImpactPoint, 200.0f);
}

bool ApassoutProjectile::removeSphereOnHit_Validate(AVoxelWorld* world, const FHitResult& Hit)
{
   	return true;
}

void ApassoutProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// This is for testing purposes for the hitbox
	// ProjectileMovement->SetVelocityInLocalSpace(FVector(0.0));

	AVoxelWorld* world = Cast<AVoxelWorld>(OtherActor);
	if(world)
	{
		removeSphereOnHit(world, Hit);
	}
	// Only add impulse and destroy projectile if we hit a physics object
	else if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherComp->IsSimulatingPhysics()))
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * VelocityMultiplier, GetActorLocation());
		Destroy();
		
	}
	else if (ApassoutCharacter* character = Cast<ApassoutCharacter>(OtherActor))
	{
		//Launches the target of the projectile in the projectile's xy direction and 45 degrees pitched upward
		FVector direction = FVector(GetVelocity());
		direction.Z = 0;
		direction.Normalize();
		FRotator rot = direction.Rotation();
		rot.Pitch = 45.0f;
		direction = rot.Vector();
		character->LaunchCharacter(direction * VelocityMultiplier * character->PlayerDamage, false, false); 
	}
}