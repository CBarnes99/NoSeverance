#pragma once

#include "CoreMinimal.h"
#include "ModalBaseClass.h"
#include "ModalOpenTurretMenu.generated.h"

UCLASS(Abstract)
class NOSEVERANCE_API UModalOpenTurretMenu : public UModalBaseClass
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

};
