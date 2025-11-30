#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PathNode.h"
#include "F_PathNodes.h"
#include "AC_NodePathLocations.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UAC_NodePathLocations : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAC_NodePathLocations();

	/**
	* @breif Get The path node locations
	* @return Gets the path node locations, as a TArray<FVector>
	*/
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetPathNodesLocations();

protected:
	virtual void BeginPlay() override;

	/**
	* @brief A TArray of path nodes to make up a path for an actor to follow, as a TArray<APathNode>
	* These are set within the editor
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<F_PathNodes> pathNodes;

	/**
	* @brief The Location of each node, as a TArray<FVector>
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FVector> pathNodeLocations;

	/**
	* @brief Gets a random index within range of the array
	* @param array The array that holds the path nodes, as a TArray<F_PathNodes>
	* @return The random int within range of the array, as an int
	*/
	UFUNCTION(BlueprintCallable)
	int GetRandomIndexInArray(TArray<F_PathNodes> array);
};
