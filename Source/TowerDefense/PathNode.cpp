#include "PathNode.h"
#include "Components/StaticMeshComponent.h"

APathNode::APathNode()
{
	PrimaryActorTick.bCanEverTick = false;

	nodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Node Mesh"));
}

void APathNode::BeginPlay()
{
	Super::BeginPlay();

	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void APathNode::OnConstruction(const FTransform& Transform)
{
	if (nodeMaterial)
	{
		nodeMesh->SetMaterial(0, nodeMaterial);
	}
}


