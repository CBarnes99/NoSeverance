#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDPlayerHud.generated.h"

class UHUDHealthAndMana;
class UHUDWeaponTurretSelector;
class UHUDCrosshair;
class UHUDPlayerCurrency;
class UHUDBaseHealth;
class UHUDAmountOfEnemiesInWave;
class UHUDAmountOfWaves;
class UDA_TurretInfo;


UCLASS(Abstract)
class NOSEVERANCE_API UHUDPlayerHud : public UUserWidget
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

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDBaseHealth* BaseHealth;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDAmountOfWaves* AmountOfWaves;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHUDAmountOfEnemiesInWave* AmountOfEnemies;


	UFUNCTION(BlueprintCallable)
	void SetLastWaveText(int lastWave);

	UFUNCTION(BlueprintCallable)
	void UpdateCurretWaveText();

	UFUNCTION(BlueprintCallable)
	void SetMaxAmountOfEnemiesText(int maxEnemies);

	UFUNCTION(BlueprintCallable)
	void UpdateCurrentAmountOfEnemiesText();

	UFUNCTION(BlueprintCallable)
	void GetInfoFromTurretMenu(bool bIsChecked, UDA_TurretInfo* turretInformation);

	UFUNCTION(BlueprintCallable)
	UDA_TurretInfo* GetTurretClassFromArray(int index);

	UFUNCTION(BlueprintCallable)
	void UpdateHealthBar(float currentHealth, float maxHealth);

	UFUNCTION(BlueprintCallable)
	void UpdateManaBar(float currentMana, float maxMana);




};
