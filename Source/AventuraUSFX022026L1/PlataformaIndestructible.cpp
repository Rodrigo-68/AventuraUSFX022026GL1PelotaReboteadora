#include "PlataformaIndestructible.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"

APlataformaIndestructible::APlataformaIndestructible()
{
	// Asigna el material azul para diferenciarla visualmente
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(
		TEXT("Material'/Game/StarterContent/Materials/M_Indestructible/M_Indestructible.M_Indestructible'"));

	if (MaterialAsset.Succeeded() && mallaPlataforma != nullptr)
	{
		mallaPlataforma->SetMaterial(0, MaterialAsset.Object);
	}
}