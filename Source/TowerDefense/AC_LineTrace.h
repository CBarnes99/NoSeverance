// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionQueryParams.h"
#include "AC_LineTrace.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UAC_LineTrace : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_LineTrace();

	UFUNCTION(BlueprintCallable)
	FVector GetTraceTargetLocation(FVector traceStartLocation, FVector actorForwardVector, float traceDistance);

	UFUNCTION(BlueprintCallable)
	void SetIgnoredActors(TArray<AActor*> ignoredActor);

	UFUNCTION(BlueprintCallable)
	void SetIgnoredActor(AActor* ignoredActor);

	UFUNCTION(BlueprintCallable)
	bool HasImpactPoint(FVector traceStartLocation, FVector actorForwardVector, float traceDistance);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FCollisionQueryParams params;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UClass* ignoredActorClass;
};
