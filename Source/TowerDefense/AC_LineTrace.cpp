#include "AC_LineTrace.h"
#include "DrawDebugHelpers.h"

UAC_LineTrace::UAC_LineTrace()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAC_LineTrace::BeginPlay()
{
	Super::BeginPlay();	
}

FVector UAC_LineTrace::GetTraceTargetLocation(FVector traceStartLocation, FVector actorForwardVector, float traceDistance)
{
	FVector targetPos = FVector::ZeroVector;
	//FHitResult hit;
	TArray<FHitResult> hits;
	FVector traceEnd = traceStartLocation + actorForwardVector * traceDistance;

	params.AddIgnoredActor(GetOwner());

	//GetWorld()->LineTraceSingleByChannel(hit, traceStartLocation, traceEnd, ECC_Pawn, params);

	GetWorld()->LineTraceMultiByChannel(hits, traceStartLocation, traceEnd, ECC_Visibility, params);

	DrawDebugLine(GetWorld(), traceStartLocation, traceEnd, FColor::Red, false, 1.f, 1.f);

	for (const FHitResult& Hit : hits)
	{
		if (Hit.GetActor() && !Hit.GetActor()->IsA(ignoredActorClass))
		{
			return Hit.ImpactPoint;
		}
	}
	//targetPos = hit.bBlockingHit ? hit.ImpactPoint : traceEnd;

	return traceEnd;
	//return targetPos;
};

void UAC_LineTrace::SetIgnoredActors(TArray<AActor*> ignoredActor)
{
	params.AddIgnoredActors(ignoredActor);
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
