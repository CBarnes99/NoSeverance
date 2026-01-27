#include "InvisableWall.h"
#include "Components/StaticMeshComponent.h"

AInvisableWall::AInvisableWall()
{
	PrimaryActorTick.bCanEverTick = false;

	invisableWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Invisable Wall"));
}

void AInvisableWall::BeginPlay()
{
	Super::BeginPlay();

	invisableWallMesh->SetVisibility(false);
}

