#include "PlataformaDestructible.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"

APlataformaDestructible::APlataformaDestructible()
{
	// Asigna el material rojo para diferenciarla visualmente
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(
		TEXT("Material'/Game/StarterContent/Materials/M_Indestructible/M_Destructible.M_Destructible'"));

	if (MaterialAsset.Succeeded() && mallaPlataforma != nullptr)
	{
		mallaPlataforma->SetMaterial(0, MaterialAsset.Object);
	}
}