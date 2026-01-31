#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "HUDButton.generated.h"


UCLASS()
class NOSEVERANCE_API UHUDButton : public UButton
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* clickSound;

protected:

	UHUDButton();

	virtual void SynchronizeProperties() override;

	UFUNCTION()
	void PlaySoundEffect();
	
};
