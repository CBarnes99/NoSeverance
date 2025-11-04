#include "AC_PreviewMesh.h"


UAC_PreviewMesh::UAC_PreviewMesh()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAC_PreviewMesh::BeginPlay()
{
	Super::BeginPlay();
}

void UAC_PreviewMesh::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAC_PreviewMesh::SetOutlineMaterial(UStaticMeshComponent* staticMesh)
{
	if (outlineMaterial)
	{
		staticMesh->SetMaterial(0, outlineMaterial);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Outline Material in AC_PreviewMesh for %s"), *GetOwner()->GetName())
	}
}

void UAC_PreviewMesh::SetNormalMaterial(UStaticMeshComponent* staticMesh)
{
	if (outlineMaterial)
	{
		staticMesh->SetMaterial(0, normalMaterial);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Normal Material in AC_PreviewMesh for %s"), *GetOwner()->GetName())
	}
}


