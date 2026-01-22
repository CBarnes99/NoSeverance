#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_CheckBool.generated.h"

UCLASS(Blueprintable)
class NOSEVERANCE_API UBTDecorator_CheckBool : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UBTDecorator_CheckBool();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
