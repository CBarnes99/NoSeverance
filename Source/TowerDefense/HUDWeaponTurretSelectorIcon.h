#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWeaponTurretSelectorIcon.generated.h"

class UImage;

UCLASS(Abstract)
class TOWERDEFENSE_API UHUDWeaponTurretSelectorIcon : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* iconImage;

	UPROPERTY(VisibleDefaultsOnly)
	TSubclassOf<UClass> weaponOrTurretClass;

	UFUNCTION(BlueprintCallable)
	void SetWidgetDefaults(UTexture2D* iconTexture, TSubclassOf<UClass> iconClass);

};
