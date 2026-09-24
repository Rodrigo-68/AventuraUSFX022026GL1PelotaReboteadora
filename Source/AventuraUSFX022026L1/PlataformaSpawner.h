#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlataformaSpawner.generated.h"

class APlataformaIndestructible;
class APlataformaDestructible;

UCLASS()
class AVENTURAUSFX022026L1_API APlataformaSpawner : public AActor
{
    GENERATED_BODY()

public:
    APlataformaSpawner();

    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<APlataformaIndestructible> IndestructibleClass;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<APlataformaDestructible> DestructibleClass;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    float AnchoArea = 300.0f;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    float IntervaloSpawn = 5.0f;
    UPROPERTY(VisibleAnywhere)
    class USceneComponent* RootScene;

protected:
    virtual void BeginPlay() override;

    void SpawnAleatorio();

    FTimerHandle SpawnTimerHandle;
};