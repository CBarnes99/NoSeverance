#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDCrosshair.generated.h"

class UImage;

UCLASS(Abstract)
class NOSEVERANCE_API UHUDCrosshair : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Crosshair;
};
