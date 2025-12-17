#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/VerticalBox.h"
#include "TurretStatic.h"
#include "HUDTurretInfo.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCheckboxStateChanged, bool, bIsChecked);

UCLASS(Abstract)
class TOWERDEFENSE_API UHUDTurretInfo : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UOverlay* WidgetOverlay;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UVerticalBox* VerticalBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TurretNameText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* TurretImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCheckBox* IsTurretSelectedCheckBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* IsTurretSelectedText;

	/*UPROPERTY(EditAnywhere, meta = (BindWidget))
	TSubclassOf<ATurretStatic> turretToSpawn;*/

	UFUNCTION(BlueprintCallable)
	void SetWidgetDefaults(FText newTurretName, UTexture2D* newTurretTexture/*, TSubclassOf<ATurretStatic> turret*/);

	//UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCheckboxStateChanged OnCheckboxStateChangedSignature;

protected:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void HandleCheckboxStateChange(bool bIsChecked);

	UFUNCTION(BlueprintCallable)
	void SetSelectedText();
};