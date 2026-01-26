#include "ModalBaseClass.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"

void UModalBaseClass::NativeConstruct()
{
	modalDisplayTime = 5.f;
	OnAnimationFinishedEvent.BindDynamic(this, &UModalBaseClass::OnEndAnimationFinished);
	BindToAnimationFinished(fadeOutAnimation, OnAnimationFinishedEvent);
}

void UModalBaseClass::PlayStartAnimation()
{
	if (!fadeInAnimation)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayAnimation: ANIMATION NOT SET WITHIN - %s"), *this->GetName());
		return;
	}

	PlayAnimation(fadeInAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);

	if (GetWorld()->GetTimerManager().IsTimerActive(EndAnimationTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(EndAnimationTimerHandle);
	}
	GetWorld()->GetTimerManager().SetTimer(EndAnimationTimerHandle, this, &UModalBaseClass::PlayEndAnimation, modalDisplayTime, false);
}

void UModalBaseClass::PlayEndAnimation()
{
	PlayAnimation(fadeOutAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
}

void UModalBaseClass::OnEndAnimationFinished()
{
	UE_LOG(LogTemp, Display, TEXT("OnEndAnimationFinished: Set Visability of %s to Collapsed"), *this->GetName());
	SetVisibility(ESlateVisibility::Collapsed);
}

void UModalBaseClass::SetText(FText newText)
{
	text->SetText(newText);
}
