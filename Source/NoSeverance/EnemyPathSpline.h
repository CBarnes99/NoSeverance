#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyPathSpline.generated.h"

class USplineComponent;
class UArrowComponent;

UCLASS()
class NOSEVERANCE_API AEnemyPathSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyPathSpline();

	/** Gets all the locations of the points within the spline */
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSplinePointLocations();

protected:
	virtual void BeginPlay() override;

	void OnConstruction(const FTransform& Transform) override;

	/** The Spline Path*/
	UPROPERTY(EditDefaultsOnly)
	USplineComponent* splinePath;

	/** An arrow to show the direction of the spline */
	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* arrow;

};
