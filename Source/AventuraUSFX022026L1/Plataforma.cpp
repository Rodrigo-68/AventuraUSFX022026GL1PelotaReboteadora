// Fill out your copyright notice in the Description page of Project Settings.


#include "Plataforma.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values
APlataforma::APlataforma()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component for the projectile sphere
	mallaPlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaPlataforma"));
	mallaPlataforma->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	mallaPlataforma->SetCollisionProfileName(TEXT("BlockAll"));
	mallaPlataforma->SetNotifyRigidBodyCollision(true); // <-- NUEVO: garantiza que ambas subclases generen OnHit
	RootComponent = mallaPlataforma;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlataformaMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));

	if (PlataformaMeshAsset.Succeeded())
	{
		mallaPlataforma->SetStaticMesh(PlataformaMeshAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Plataforma: no se encontro el StaticMesh Shape_Plane en la ruta esperada"));
	}

	/*
	ZMax = 800.0f;
	ZMin = 200.0f;
	Velocidad = 100.0f;
	Signo = 1.0f;
	*/

	movimientoEjes = FVector(1.0f, 0.0f, 0.0f);
	movimientoLimitesMaximos = FVector(FMath::RandRange(200.0f, 800.0f), FMath::RandRange(200.0f, 800.0f), FMath::RandRange(200.0f, 800.0f));
	movimientoLimitesMinimos = FVector(FMath::RandRange(-800.0f, -200.0f), FMath::RandRange(-800.0f, -200.0f), FMath::RandRange(-800.0f, -200.0f));
	movimientoVelocidades = FVector(FMath::RandRange(50.0f, 200.0f), FMath::RandRange(50.0f, 200.0f), FMath::RandRange(50.0f, 200.0f));
	movimientoDireccion = FVector(FMath::RandRange(-1.0f, 1.0f), FMath::RandRange(-1.0f, 1.0f), FMath::RandRange(-1.0f, 1.0f));
	//movimientoDireccion = FVector(1.0f, 0.0f, 0.0f);

	TiempoTranscurrido = 0.0f;
}

// Called when the game starts or when spawned
void APlataforma::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ca�da recta hacia abajo (Lab 01)
	AddActorWorldOffset(FVector(0.f, 0.f, -VelocidadCaida * DeltaTime), true);

	// Se destruye si cae fuera del �rea jugable (evita acumulaci�n infinita)
	/*if (GetActorLocation().Z < -200.0f)
	{
		Destroy();
		return;
	*/

	TiempoTranscurrido += DeltaTime;

}