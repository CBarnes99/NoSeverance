#include "HUDTurretSelectionMenu.h"

void UHUDTurretSelectionMenu::NativeConstruct()
{
	TArray<UWidget*> gridChildren = TurretSelectionGrid->GetAllChildren();

	for (UWidget* widget : gridChildren)
	{
		if (UHUDTurretInfo* turretWidget = Cast<UHUDTurretInfo>(widget))
		{
			turretWidget->OnCheckboxStateChangedSignature.AddDynamic(this, &UHUDTurretSelectionMenu::TurretHasBeenSelected);
		}
	}
}

void UHUDTurretSelectionMenu::TurretHasBeenSelected(bool bIsChecked)
{
	UE_LOG(LogTemp, Warning, TEXT("Checkbox is doing things"));
}