#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetPathNodeLocation.generated.h"

UCLASS()
class NOSEVERANCE_API UBTTask_SetPathNodeLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	explicit UBTTask_SetPathNodeLocation(FObjectInitializer const& ObjectInitializer);

	/** A created task to set the location for the next path node for the enemy to follow */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};