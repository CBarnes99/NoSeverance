#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyAIController.generated.h"

UCLASS()
class TOWERDEFENSE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:

	virtual void OnPossess(APawn* InPawn) override;
};
