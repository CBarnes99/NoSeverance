#include "BTDecorator_CheckBool.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CheckBool::UBTDecorator_CheckBool()
{
	NodeName = TEXT("Check Blackboard Bool");
}

bool UBTDecorator_CheckBool::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();
	if (!blackboardComp)
	{
		UE_LOG(LogTemp, Error, TEXT("NO BLACKBOARD COMP WITHIN - %s"), *this->GetName());
		false;
	}

	//bool bValue = blackboardComp->GetValueAsBool(GetSelectedBlackboardKey());
	return blackboardComp->GetValueAsBool(BlackboardKey.SelectedKeyName);

	//return bValue;
}
