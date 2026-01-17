#include "Core_GameState.h"
#include "DefendingBase.h"
#include "Kismet/GameplayStatics.h"

void ACore_GameState::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s has initilized!"), *this->GetName());

	if (playerCurrencyAmount == NULL)
	{
		playerCurrencyAmount = 100;
		UE_LOG(LogTemp, Error, TEXT("BeginPlay: Player Currency was not set! Set to 100 by Default!"))
	}

	if (maxListSizeInWeaponTurretHud == NULL)
	{
		maxListSizeInWeaponTurretHud = 5;
		UE_LOG(LogTemp, Error, TEXT("BeginPlay: amountInWeaponTurretHud was not set! Set to 5 by Default!"))
	}
	
	currentListSizeInWeaponTurretHud = 0;

	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ADefendingBase::StaticClass());
	ADefendingBase* defendingBase = Cast<ADefendingBase>(actor);
	if (!defendingBase)
	{
		UE_LOG(LogTemp, Error, TEXT("BeginPlay: defendingBase NOT CASTED CORRECTLY WITHIN - %s"), *this->GetName());
	}
	defendingBase->BaseHealthReachedZeroEvent.BindUObject(this, &ACore_GameState::PlayerHasLost);
}

void ACore_GameState::PlayerHasLost()
{
	OnPlayerLostEvent.Broadcast();
}

float ACore_GameState::GetPlayerCurrencyAmount()
{
	return playerCurrencyAmount;
}

void ACore_GameState::UpdatePlayerCurrencyAmount(bool addCurrency, int amount)
{
	if (addCurrency)
	{
		playerCurrencyAmount = playerCurrencyAmount + amount;
	}
	else
	{
		playerCurrencyAmount = playerCurrencyAmount - amount;
	}

	PlayerCurrencyUpdatedEvent.Broadcast(playerCurrencyAmount);
}

int ACore_GameState::GetMaxListSizeInWeaponTurretHud()
{
	return maxListSizeInWeaponTurretHud;
}

void ACore_GameState::SetMaxListSizeInWeaponTurretHud(int newMax)
{
	maxListSizeInWeaponTurretHud = newMax;
}

int ACore_GameState::GetCurrentListSizeInWeaponTurretHud()
{
	return currentListSizeInWeaponTurretHud;
}

void ACore_GameState::UpdateCurrentListSizeInWeaponTurretHud(bool addSize)
{
	if (addSize)
	{
		currentListSizeInWeaponTurretHud++;

		if (currentListSizeInWeaponTurretHud > maxListSizeInWeaponTurretHud)
		{
			UE_LOG(LogTemp, Error, TEXT("UpdateCurrentListSizeInWeaponTurretHud: Current List Size In Weapon Turret Hud Has Exceeded Max Size!!!"))
		}
	}
	else
	{
		currentListSizeInWeaponTurretHud--;

		if (currentListSizeInWeaponTurretHud < 0)
		{
			UE_LOG(LogTemp, Error, TEXT("UpdateCurrentListSizeInWeaponTurretHud: Current List Size In Weapon Turret Hud Is Below 0!!!"))
		}
	}

	UE_LOG(LogTemp, Display, TEXT("UpdateCurrentListSizeInWeaponTurretHud: Current List Size In Weapon Turret Hud = %d"), currentListSizeInWeaponTurretHud);
}

bool ACore_GameState::IsCurrentListSizeLessThanMax()
{
	return currentListSizeInWeaponTurretHud < maxListSizeInWeaponTurretHud;
}
