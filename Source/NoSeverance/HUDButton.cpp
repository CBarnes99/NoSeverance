#include "HUDButton.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

UHUDButton::UHUDButton()
{
	static ConstructorHelpers::FObjectFinder<USoundBase> buttonPressSfx(TEXT("/Game/Audio/ButtonPressSFX.ButtonPressSFX"));
	if (buttonPressSfx.Succeeded())
	{
		clickSound = buttonPressSfx.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlaySoundEffect: Click sound effect not set within - %s"), *this->GetName());
	}

}

void UHUDButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	OnPressed.Clear();
	OnPressed.AddDynamic(this, &UHUDButton::PlaySoundEffect);
}

void UHUDButton::PlaySoundEffect()
{
	UE_LOG(LogTemp, Error, TEXT("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));


	if (clickSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), clickSound);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlaySoundEffect: Click sound effect not set for %s"), *GetName());
	}
}
