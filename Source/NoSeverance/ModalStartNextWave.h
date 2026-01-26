#pragma once

#include "CoreMinimal.h"
#include "ModalBaseClass.h"
#include "ModalStartNextWave.generated.h"

UCLASS(Abstract)
class NOSEVERANCE_API UModalStartNextWave : public UModalBaseClass
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	
};
