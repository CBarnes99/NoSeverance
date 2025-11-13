#include "DefendingBase.h"

ADefendingBase::ADefendingBase()
{
	PrimaryActorTick.bCanEverTick = false;

	base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	base->SetupAttachment(RootComponent.Get());

}

// Called when the game starts or when spawned
void ADefendingBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefendingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

