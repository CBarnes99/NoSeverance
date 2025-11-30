#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathNode.generated.h"

UCLASS()
class TOWERDEFENSE_API APathNode : public AActor
{
	GENERATED_BODY()
	
public:	
	APathNode();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "PathNode")
	class UStaticMeshComponent* nodeMesh;

	UPROPERTY(EditAnywhere, Category = "PathNode")
	UMaterialInterface* nodeMaterial;

	virtual void OnConstruction(const FTransform& Transform) override;
};
