#include "AC_LineTrace.h"
#include "DrawDebugHelpers.h"

UAC_LineTrace::UAC_LineTrace()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAC_LineTrace::BeginPlay()
{
	Super::BeginPlay();	
}

FVector UAC_LineTrace::GetTraceTargetLocation(FVector traceStartLocation, FVector actorForwardVector, float traceDistance)
{
	FVector targetPos = FVector::ZeroVector;
	TArray<FHitResult> hits;
	FVector traceEnd = traceStartLocation + actorForwardVector * traceDistance;

	params.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceMultiByChannel(hits, traceStartLocation, traceEnd, ECC_Visibility, params);

	DrawDebugLine(GetWorld(), traceStartLocation, traceEnd, FColor::Red, false, 1.f, 1.f);

	for (const FHitResult& Hit : hits)
	{
		if (Hit.GetActor() && !Hit.GetActor()->IsA(ignoredActorClass))
		{
			return Hit.ImpactPoint;
		}
	}
	return traceEnd;
};

void UAC_LineTrace::SetIgnoredActors(TArray<AActor*> ignoredActors)
{
	params.AddIgnoredActors(ignoredActors);
}
void UAC_LineTrace::SetIgnoredActor(AActor* ignoredActor)
{
	ignoredActorClass = ignoredActor->GetClass();
}

bool UAC_LineTrace::HasImpactPoint(FVector traceStartLocation, FVector actorForwardVector, float traceDistance)
{
	FVector targetPos = FVector::ZeroVector;
	TArray<FHitResult> hits;
	FVector traceEnd = traceStartLocation + actorForwardVector * traceDistance;

	params.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceMultiByChannel(hits, traceStartLocation, traceEnd, ECC_Visibility, params);

	DrawDebugLine(GetWorld(), traceStartLocation, traceEnd, FColor::Red, false, 1.f, 1.f);

	for (const FHitResult& Hit : hits)
	{
		if (Hit.GetActor() && !Hit.GetActor()->IsA(ignoredActorClass))
		{
			return true;
		}
	}

	return false;
}
