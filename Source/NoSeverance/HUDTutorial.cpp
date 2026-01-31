#include "HUDTutorial.h"
#include "HUDButton.h"

void UHUDTutorial::NativeConstruct()
{
	closeButton->OnPressed.AddDynamic(this, &UHUDTutorial::OnButtonPressed);
}

void UHUDTutorial::OnButtonPressed()
{
	UE_LOG(LogTemp, Display, TEXT("OnButtonPressed: Close Button Pressed within HUDTutorial"));
	CloseTutorialEvent.ExecuteIfBound();
}
