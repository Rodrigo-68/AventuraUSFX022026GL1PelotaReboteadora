// Copyright Epic Games, Inc. All Rights Reserve

#include "AventuraUSFX022026L1Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "PlataformaDestructible.h"

AAventuraUSFX022026L1Projectile::AAventuraUSFX022026L1Projectile() 
{
	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AAventuraUSFX022026L1Projectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	// --- NUEVO: que rebote indefinidamente en vez de destruirse ---
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1.0f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->bBounceAngleAffectsFriction = false;

	// Die after 3 seconds by default
	InitialLifeSpan = 0.f;
}

void AAventuraUSFX022026L1Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		// Si choca con una PlataformaDestructible, esa plataforma se destruye
		if (APlataformaDestructible* Destructible = Cast<APlataformaDestructible>(OtherActor))
		{
			Destructible->Destroy();
		}
		// Si choca con PlataformaIndestructible o una pared: no hacemos nada.
		// El rebote ya lo maneja automáticamente ProjectileMovementComponent (bShouldBounce).
	}

	// IMPORTANTE: ya NO llamamos Destroy() aquí — la pelota nunca se destruye a sí misma.
}