#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetPlayerLocation.generated.h"

UCLASS()
class TOWERDEFENSE_API UBTTask_GetPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	explicit UBTTask_GetPlayerLocation(FObjectInitializer const& ObjectInitializer);

	/** A created task to set the location of the player for the enemy to move towards */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
