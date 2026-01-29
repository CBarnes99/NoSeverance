#include "HUDAmountOfWaves.h"
#include "Components/TextBlock.h"

void UHUDAmountOfWaves::NativeConstruct()
{
	currentWave = 0;
	lastWave = 0;
}

void UHUDAmountOfWaves::SetMaxWave(int amount)
{
	lastWave = amount;
}

void UHUDAmountOfWaves::UpdateText()
{
	currentWave++;

	FText formatText = FText::FromString(TEXT("Wave: {current}/{max}"));
	FFormatNamedArguments args;
	args.Add(TEXT("current"), currentWave);
	args.Add(TEXT("max"), lastWave);

	amountOfWavesText->SetText(FText::Format(formatText, args));

}