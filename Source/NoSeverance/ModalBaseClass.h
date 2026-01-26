#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ModalBaseClass.generated.h"

class UWidgetAnimation;
class UTextBlock;

UCLASS(Abstract)
class NOSEVERANCE_API UModalBaseClass : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayStartAnimation();

	UFUNCTION(BlueprintCallable)
	void SetText(FText newText);

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly)
	float modalDisplayTime;

	FWidgetAnimationDynamicEvent OnAnimationFinishedEvent;

	FTimerHandle EndAnimationTimerHandle;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* text;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* fadeInAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* fadeOutAnimation;

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayEndAnimation();

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void OnEndAnimationFinished();

};
