// Copyright Epic Games, Inc. All Rights Reserved.

#include "AventuraUSFX022026L1GameMode.h"
#include "AventuraUSFX022026L1Pawn.h"
#include "Plataforma.h"
#include "PlataformaAerea.h"
#include "PlataformaTerrestre.h"
#include "PlataformaSubterranea.h"
#include "PlataformaAcuatica.h"

AAventuraUSFX022026L1GameMode::AAventuraUSFX022026L1GameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AAventuraUSFX022026L1Pawn::StaticClass();

	tipoPlataformaActual = 0;
}

void AAventuraUSFX022026L1GameMode::BeginPlay()
{
	Super::BeginPlay();

	// --- BLOQUE DESACTIVADO: generaci�n masiva de plataformas de un laboratorio anterior ---
	// (PlataformaAerea/Terrestre/Subterranea/Acuatica) - no corresponde al Lab01.
	// El Lab01 usa PlataformaSpawner (uno por �rea) en vez de este spawn masivo aleatorio.
	/*
	UWorld* World = GetWorld();

	if (World == nullptr)
	{
		return;
	}

	FRotator Rotacion = FRotator::ZeroRotator;
	FVector SpawnLocation = FVector::ZeroVector;

	APlataforma* plataformaActual;
	int tipoPlataformaRandom;

	for (int i = 0; i < 50; i++) {

		SpawnLocation = FVector(FMath::RandRange(-1500.0f, 1500.0f), FMath::RandRange(-1500.0f, 1500.0f), FMath::RandRange(50.0f, 1000.0f));

		tipoPlataformaRandom = FMath::RandRange(0, 3);

		switch (tipoPlataformaRandom) {
			case 0:
				plataformaActual = World->SpawnActor<APlataformaAerea>(SpawnLocation, Rotacion);
				break;
			case 1:
				plataformaActual = World->SpawnActor<APlataformaTerrestre>(SpawnLocation, Rotacion);
				break;
			case 2:
				plataformaActual = World->SpawnActor<APlataformaSubterranea>(SpawnLocation, Rotacion);
				break;
			case 3:
				plataformaActual = World->SpawnActor<APlataformaAcuatica>(SpawnLocation, Rotacion);
				break;
			default:
				break;
			}

		aPlataformas.Add(plataformaActual);

	}

	GetWorldTimerManager().SetTimer(TimerEliminarPlataforma, this, &AAventuraUSFX022026L1GameMode::EliminarPlataforma, 1.0f, true);
	*/
}

void AAventuraUSFX022026L1GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAventuraUSFX022026L1GameMode::EliminarPlataforma()
{
	// Desactivado junto con el bloque de spawn masivo del laboratorio anterior (ver BeginPlay).
	/*
	for (int32 i = 0; i < aPlataformas.Num(); i++)
	{
		if (aPlataformas[i] != nullptr)
		{
			APlataforma* plataformaActual = aPlataformas[i];

			if (plataformaActual != nullptr)
			{
				if (plataformaActual->tipoPlataforma == static_cast<ETipoPlataforma>(tipoPlataformaActual))
				{
					plataformaActual->Destroy();
					aPlataformas.RemoveAt(i);
					break;
				}
			}
		}
	}
	if (tipoPlataformaActual >= 3)
	{
		tipoPlataformaActual = 0;
	}
	else
		tipoPlataformaActual++;
	*/
}