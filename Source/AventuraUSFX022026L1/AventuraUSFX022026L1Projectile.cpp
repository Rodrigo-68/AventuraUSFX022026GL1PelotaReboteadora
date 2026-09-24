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
	UE_LOG(LogTemp, Warning, TEXT("Constructor de Projectile ejecutado"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->SetGenerateOverlapEvents(false);
	ProjectileMesh->SetNotifyRigidBodyCollision(true);
	ProjectileMesh->BodyInstance.bUseCCD = true;
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AAventuraUSFX022026L1Projectile::OnHit);
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 1800.f;
	ProjectileMovement->MaxSpeed = 1800.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	// IMPORTANTE: debe quedar en true para que el componente no se detenga al chocar.
	// El rebote real lo controla manualmente OnHit() con MirrorByVector.
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.98f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->bBounceAngleAffectsFriction = false;

	InitialLifeSpan = 0.f;
}

void AAventuraUSFX022026L1Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile::OnHit disparado"));

	if (OtherActor != nullptr && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pelota golpeo a: %s (clase: %s)"), *OtherActor->GetName(), *OtherActor->GetClass()->GetName());

		if (APlataformaDestructible* Destructible = Cast<APlataformaDestructible>(OtherActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("Cast a Destructible exitoso -> destruyendo %s"), *Destructible->GetName());
			Destructible->Destroy();
			return;
		}

		// Rebote manual: refleja la velocidad respecto a la normal del impacto,
		// con una peque�a variaci�n aleatoria para evitar bucles cerrados en esquinas.
		FVector CurrentVelocity = ProjectileMovement->Velocity;

		// En golpes muy rasantes o de barrido rapido, Hit.ImpactNormal puede llegar
		// como vector cero; en ese caso usamos Hit.Normal como respaldo para no perder el rebote.
		FVector ImpactNormal = Hit.ImpactNormal;
		if (!ImpactNormal.Normalize())
		{
			ImpactNormal = Hit.Normal;
			ImpactNormal.Normalize();
		}

		UE_LOG(LogTemp, Warning, TEXT("Rebote: normal=%s velocidadPrevia=%s"), *ImpactNormal.ToString(), *CurrentVelocity.ToString());

		FVector ReflectedVelocity = CurrentVelocity.MirrorByVector(ImpactNormal);

		float AnguloExtra = FMath::RandRange(-5.0f, 5.0f);
		ReflectedVelocity = ReflectedVelocity.RotateAngleAxis(AnguloExtra, FVector(0.f, 0.f, 1.f));

		ProjectileMovement->Velocity = ReflectedVelocity;

		UE_LOG(LogTemp, Warning, TEXT("Rebote: velocidadNueva=%s"), *ReflectedVelocity.ToString());
	}
}