#include "HUDBaseHealth.h"
#include "Kismet/GameplayStatics.h"
#include "DefendingBase.h"
#include "Components/TextBlock.h"

void UHUDBaseHealth::NativeConstruct()
{
	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ADefendingBase::StaticClass());
	ADefendingBase* defendingBase = Cast<ADefendingBase>(actor);
	if (defendingBase)
	{
		defendingBase->BaseHealthDecreasedEvent.BindUObject(this, &UHUDBaseHealth::UpdateBaseHealthHUD);
		UpdateBaseHealthHUD(defendingBase->GetBaseHealth());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Defending Base Wasn't Casted Correctly within - %s"), *this->GetName());
	}
}

void UHUDBaseHealth::UpdateBaseHealthHUD(int healthValue)
{
	FString valueAsString = FString::FromInt(healthValue);

	baseHealthText->SetText(FText::FromString(valueAsString));
}
