#include "HUDPlayerCurrency.h"
#include "Core_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UHUDPlayerCurrency::NativeConstruct()
{
	AGameStateBase* gameState = UGameplayStatics::GetGameState(GetWorld());
	ACore_GameState* coreGameState = Cast<ACore_GameState>(gameState);
	coreGameState->PlayerCurrencyUpdatedEvent.AddDynamic(this, &UHUDPlayerCurrency::SetTextToPlayerCurrency);
	coreGameState->PlayerCurrencyUpdatedEvent.Broadcast(coreGameState->GetPlayerCurrencyAmount());
}

void UHUDPlayerCurrency::SetTextToPlayerCurrency(float amount)
{
	FString floatAsString = FString::SanitizeFloat(amount);
	CurrencyText->SetText(FText::FromString(floatAsString));
}
