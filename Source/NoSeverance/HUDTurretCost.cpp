#include "HUDTurretCost.h"
#include "Components/TextBlock.h"

void UHUDTurretCost::NativeConstruct()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UHUDTurretCost::SetTurretCost(int price)
{
	FText formatText = FText::FromString(TEXT("Turret Cost: {cost}"));
	FFormatNamedArguments args;
	args.Add(TEXT("cost"), price);

	turretCostText->SetText(FText::Format(formatText, args));
}

void UHUDTurretCost::IsTurretPriceVisable(bool bIsVisable)
{
	if (bIsVisable)
	{
		this->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		this->SetVisibility(ESlateVisibility::Collapsed);
	}
}
