#include "HUDAmountOfEnemiesInWave.h"
#include "Components/TextBlock.h"

void UHUDAmountOfEnemiesInWave::NativeConstruct()
{
	maxEnemiesInWave = 0;
	currentEnemiesInWave = 0;
}

void UHUDAmountOfEnemiesInWave::SetMaxAmountOfEnemiesText(int amount)
{
	maxEnemiesInWave = amount;
	currentEnemiesInWave = amount + 1;

	UpdateText();
}

void UHUDAmountOfEnemiesInWave::UpdateText()
{
	currentEnemiesInWave--;

	FText formatText = FText::FromString(TEXT("Empolyees: {current}/{max}"));
	FFormatNamedArguments args;
	args.Add(TEXT("current"), currentEnemiesInWave);
	args.Add(TEXT("max"), maxEnemiesInWave);

	amountOfEnemiesText->SetText(FText::Format(formatText, args));
}
