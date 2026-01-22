#include "HUDPlayerCurrency.h"
#include "Core_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UHUDPlayerCurrency::NativeConstruct()
{
	AGameStateBase* gameState = UGameplayStatics::GetGameState(GetWorld());
	ACore_GameState* coreGameState = Cast<ACore_GameState>(gameState);
	coreGameState->PlayerCurrencyUpdatedEvent.BindUObject(this, &UHUDPlayerCurrency::SetTextToPlayerCurrency);
	coreGameState->PlayerCurrencyUpdatedEvent.ExecuteIfBound(coreGameState->GetPlayerCurrencyAmount());
}

void UHUDPlayerCurrency::SetTextToPlayerCurrency(int amount)
{
	FString intAsString = FString::FromInt(amount);
	CurrencyText->SetText(FText::FromString(intAsString));
}
