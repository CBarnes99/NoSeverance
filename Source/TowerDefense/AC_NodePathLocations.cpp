#include "AC_NodePathLocations.h"

UAC_NodePathLocations::UAC_NodePathLocations()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UAC_NodePathLocations::BeginPlay()
{
	Super::BeginPlay();
}

TArray<FVector> UAC_NodePathLocations::GetPathNodesLocations()
{
	pathNodeLocations.Empty();

	if (!pathNodes.IsValidIndex(0))
	{
		UE_LOG(LogTemp, Error, TEXT("No Nodes for the path within - %s"), *GetOwner()->GetName());
		return TArray<FVector>();
	}
	int randomIndex = GetRandomIndexInArray(pathNodes);

	if (randomIndex == INDEX_NONE)
	{
		UE_LOG(LogTemp, Error, TEXT("No Nodes for the path within - %s"), *GetOwner()->GetName());
		return TArray<FVector>();
	}
	
	for (APathNode* element : pathNodes[randomIndex].pathNodes)
	{
		pathNodeLocations.Add(element->GetActorLocation());
	}
	return pathNodeLocations;
}


int UAC_NodePathLocations::GetRandomIndexInArray(TArray<F_PathNodes> array)
{
	int count = array.Num();
	if (count == 0)
	{
		return INDEX_NONE;
	}
	int randomIndex = FMath::RandRange(0, count - 1);
	return randomIndex;
}