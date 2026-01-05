#include "BTTask_GetPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_GetPlayerLocation::UBTTask_GetPlayerLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Player Location");

}

EBTNodeResult::Type UBTTask_GetPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();

	if (!blackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("NO BLACKBOARD WITHIN - %s"), *this->GetName());
		return EBTNodeResult::Failed;
	}

	UObject* playerUObject = blackBoard->GetValueAsObject("PlayerActor");

	if (!playerUObject)
	{
		UE_LOG(LogTemp, Error, TEXT("PLAYER UOBJECT VALUE NOT FOUND WITHIN - %s"), *this->GetName());
		return EBTNodeResult::Failed;
	}

	AActor* playerActor = Cast<AActor>(playerUObject);
	if (!playerActor)
	{
		UE_LOG(LogTemp, Error, TEXT("PLAYER ACTOR VALUE NOT FOUND WITHIN - %s"), *this->GetName());
		return EBTNodeResult::Failed;
	}

	blackBoard->SetValueAsVector("PlayerLocation", playerActor->GetActorLocation());
	return EBTNodeResult::Succeeded;
}
