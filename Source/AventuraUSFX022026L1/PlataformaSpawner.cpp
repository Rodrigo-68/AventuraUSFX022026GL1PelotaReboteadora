#include "PlataformaSpawner.h"
#include "PlataformaIndestructible.h"
#include "PlataformaDestructible.h"
#include "Kismet/GameplayStatics.h"

APlataformaSpawner::APlataformaSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;
}

void APlataformaSpawner::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this,
        &APlataformaSpawner::SpawnAleatorio, IntervaloSpawn, true);
}

void APlataformaSpawner::SpawnAleatorio()
{
    UE_LOG(LogTemp, Warning, TEXT("SpawnAleatorio ejecutado en %s"), *GetName());

    if (!IndestructibleClass || !DestructibleClass) return;

    FVector Loc = GetActorLocation();
    Loc.X += FMath::FRandRange(-AnchoArea / 2.0f, AnchoArea / 2.0f);
    Loc.Z += 500.0F; // Ajuste para que la plataforma aparezca un poco más arriba

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    AActor* NuevaPlataforma = nullptr;

    if (FMath::RandBool())
        NuevaPlataforma = GetWorld()->SpawnActor<APlataformaIndestructible>(IndestructibleClass, Loc, FRotator::ZeroRotator, Params);
    else
        NuevaPlataforma = GetWorld()->SpawnActor<APlataformaDestructible>(DestructibleClass, Loc, FRotator::ZeroRotator, Params);

    UE_LOG(LogTemp, Warning, TEXT("Spawn en %s -> %s"), *Loc.ToString(), NuevaPlataforma ? TEXT("OK") : TEXT("NULL"));
}