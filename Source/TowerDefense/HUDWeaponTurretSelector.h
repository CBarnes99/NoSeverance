#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWeaponTurretSelector.generated.h"

class UDA_TurretInfo;

UCLASS(Abstract)
class TOWERDEFENSE_API UHUDWeaponTurretSelector : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void TestDelegateFunction(bool bIsChecked, UDA_TurretInfo* turretInformation);

};
