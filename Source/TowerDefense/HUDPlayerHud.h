#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDPlayerHud.generated.h"

class UHUDHealthAndMana;
class UHUDWeaponTurretSelector;
class UHUDCrosshair;
class UHUDPlayerCurrency;

UCLASS(Abstract)
class TOWERDEFENSE_API UHUDPlayerHud : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDHealthAndMana* HealthAndMana;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDWeaponTurretSelector* WeaponAndTurretSelector;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDCrosshair* Crosshair;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDPlayerCurrency* PlayerCurrency;
};
