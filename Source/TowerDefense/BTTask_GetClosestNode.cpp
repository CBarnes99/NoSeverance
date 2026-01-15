#include "BTTask_GetClosestNode.h"
#include "AIController.h"
#include "EnemyCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_GetClosestNode::UBTTask_GetClosestNode(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Get Closest Node";
}

EBTNodeResult::Type UBTTask_GetClosestNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("ExecuteTask: No AI Controller Found within - %s"), *this->GetName());
		return EBTNodeResult::Failed;
	}

	APawn* enemyAsPawn = AIController->GetPawn();
	if (!enemyAsPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("ExecuteTask: No Controlled Pawn Failed within - %s"), *this->GetName());
		return EBTNodeResult::Failed;
	}

	AEnemyCharacterBase* enemyCharacter = Cast<AEnemyCharacterBase>(enemyAsPawn);
	if (!enemyCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("ExecuteTask: Pawn isn't of type AEnemyCharacterBase within - %s"), *this->GetName());
		return EBTNodeResult::Failed;
	}

	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(NextPathNodeLocation.SelectedKeyName, enemyCharacter->GetClosestPathNodeLocation());
	return EBTNodeResult::Succeeded;
}
