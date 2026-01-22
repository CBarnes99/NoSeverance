#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDTutorial.generated.h"

UCLASS(Abstract)
class NOSEVERANCE_API UHUDTutorial : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
};
