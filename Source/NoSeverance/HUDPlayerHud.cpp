#include "HUDPlayerHud.h"
#include "HUDAmountOfWaves.h"
#include "HUDAmountOfEnemiesInWave.h"
#include "HUDHealthAndMana.h"
#include "HUDWeaponTurretSelector.h"

void UHUDPlayerHud::SetLastWaveText(int lastWave)
{
	AmountOfWaves->SetMaxWave(lastWave);
}

void UHUDPlayerHud::UpdateCurretWaveText()
{
	AmountOfWaves->UpdateText();
}

void UHUDPlayerHud::SetMaxAmountOfEnemiesText(int maxEnemies)
{
	AmountOfEnemies->SetMaxAmountOfEnemiesText(maxEnemies);
}

void UHUDPlayerHud::UpdateCurrentAmountOfEnemiesText()
{
	AmountOfEnemies->UpdateText();
}

void UHUDPlayerHud::GetInfoFromTurretMenu(bool bIsChecked, UDA_TurretInfo* turretInformation)
{
	WeaponAndTurretSelector->GetInfoFromTurretMenu(bIsChecked, turretInformation);
}

UDA_TurretInfo* UHUDPlayerHud::GetTurretClassFromArray(int index)
{
	return WeaponAndTurretSelector->GetTurretClassFromArray(index);
}

void UHUDPlayerHud::UpdateHealthBar(float currentHealth, float maxHealth)
{
	HealthAndMana->UpdateHealthBar(currentHealth, maxHealth);
}

void UHUDPlayerHud::UpdateManaBar(float currentMana, float maxMana)
{
	HealthAndMana->UpdateManaBar(currentMana, maxMana);
}
