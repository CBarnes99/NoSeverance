#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetClosestNode.generated.h"

UCLASS()
class TOWERDEFENSE_API UBTTask_GetClosestNode : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	/** The enemy self actor Key */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector EnemyActor;

	/** Path Node Location Key */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector NextPathNodeLocation;


	explicit UBTTask_GetClosestNode(FObjectInitializer const& ObjectInitializer);

	/** A created task to set the location of the player for the enemy to move towards */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
