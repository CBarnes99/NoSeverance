#include "EnemyPathSpline.h"
#include "Components/SplineComponent.h"
#include "Components/ArrowComponent.h"

AEnemyPathSpline::AEnemyPathSpline()
{
	PrimaryActorTick.bCanEverTick = false;

	splinePath = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Path"));
	splinePath->SetSplinePointType(0, ESplinePointType::Linear);

	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	RootComponent = splinePath;
	arrow->SetupAttachment(RootComponent.Get());
}

void AEnemyPathSpline::BeginPlay()
{
	Super::BeginPlay();	
	GetSplinePointLocations();
}

void AEnemyPathSpline::OnConstruction(const FTransform& Transform)
{
	int splinePoints = splinePath->GetNumberOfSplinePoints();

	for (int i = 0; i < splinePoints; i++)
	{
		splinePath->SetSplinePointType(i, ESplinePointType::Linear, true);
	}
}

TArray<FVector> AEnemyPathSpline::GetSplinePointLocations()
{
	TArray<FVector> splinePointLocations;
	int amountOfSplinePoints = -1;

	amountOfSplinePoints = splinePath->GetNumberOfSplinePoints();
	if (amountOfSplinePoints < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("GetSplinePointLocations: NO SPLINE POINTS DETECTED WITHIN - %s... NO FVECTOR HAS BEEN ASIGNED"), *this->GetName());
		return TArray<FVector>();
	}
	
	for (int i = 0; i < amountOfSplinePoints; i++)
	{
		splinePointLocations.Add(splinePath->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World));

		/*
		UE_LOG(LogTemp, Warning, TEXT("GetSplinePointLocations: Spline point - %d"), i);
		UE_LOG(LogTemp, Warning, TEXT("GetSplinePointLocations: Location = %s"), *splinePath->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World).ToString());
		*/

	}
	return splinePointLocations;
}