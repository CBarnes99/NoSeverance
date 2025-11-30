#pragma once

#include "CoreMinimal.h"
#include "PathNode.h"
#include "F_PathNodes.generated.h"

USTRUCT(BlueprintType)
struct TOWERDEFENSE_API F_PathNodes
{
public:
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APathNode*> pathNodes;
};
