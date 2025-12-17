#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/UniformGridPanel.h"
#include "HUDTurretInfo.h"
#include "HUDTurretSelectionMenu.generated.h"

UCLASS(Abstract)
class TOWERDEFENSE_API UHUDTurretSelectionMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* MenuCanvasPanel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UUniformGridPanel* TurretSelectionGrid;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UHUDTurretInfo* Turret1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UHUDTurretInfo* Turret2;

protected:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void TurretHasBeenSelected(bool bIsChecked);
};
