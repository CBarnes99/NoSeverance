#include "HUDMainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Misc/PackageName.h"

void UHUDMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	PlayButton->OnPressed.AddDynamic(this, &UHUDMainMenu::PlayButtonFunction);
	QuitGameButton->OnPressed.AddDynamic(this, &UHUDMainMenu::QuitGameFunction);
	LevelOneButton->OnPressed.AddDynamic(this, &UHUDMainMenu::LevelOneButtonFunction);
	LevelTwoButton->OnPressed.AddDynamic(this, &UHUDMainMenu::LevelTwoButtonFunction);
	LevelThreeButton->OnPressed.AddDynamic(this, &UHUDMainMenu::LevelThreeButtonFunction);
	ReturnButton->OnPressed.AddDynamic(this, &UHUDMainMenu::ReturnButtonFunction);
}

void UHUDMainMenu::PlayButtonFunction()
{
	UE_LOG(LogTemp, Display, TEXT("PlayButtonFunction: Play Button pressed In Main Menu"));
	MenuSwitcher->SetActiveWidgetIndex(1);
}

void UHUDMainMenu::QuitGameFunction()
{
	UE_LOG(LogTemp, Display, TEXT("QuitGameFunction: Quit Game button pressed In Main Menu"));
	TEnumAsByte<EQuitPreference::Type> QuitPreference = EQuitPreference::Quit;
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), QuitPreference, true);
}

void UHUDMainMenu::ReturnButtonFunction()
{
	MenuSwitcher->SetActiveWidgetIndex(0);
}

void UHUDMainMenu::LevelOneButtonFunction()
{
	TSoftObjectPtr<UWorld> levelRef;
	if (GetLevelReferenceEvent.IsBound())
	{
		levelRef = GetLevelReferenceEvent.Execute(1);
	}
	if (!levelRef)
	{
		UE_LOG(LogTemp, Error, TEXT("LevelOneButtonFunction: Level Ref Not Valid"))
	}
	OpenLevelFromSoftObjectPtrAsync(levelRef);
}

void UHUDMainMenu::LevelTwoButtonFunction()
{
	TSoftObjectPtr<UWorld> levelRef;
	if (GetLevelReferenceEvent.IsBound())
	{
		levelRef = GetLevelReferenceEvent.Execute(2);
	}
	if (!levelRef)
	{
		UE_LOG(LogTemp, Error, TEXT("LevelTwoButtonFunction: Level Ref Not Valid"))
	}
	OpenLevelFromSoftObjectPtrAsync(levelRef);
}

void UHUDMainMenu::LevelThreeButtonFunction()
{
	TSoftObjectPtr<UWorld> levelRef;
	if (GetLevelReferenceEvent.IsBound())
	{
		levelRef = GetLevelReferenceEvent.Execute(3);
	}
	if (!levelRef)
	{
		UE_LOG(LogTemp, Error, TEXT("LevelThreeButtonFunction: Level Ref Not Valid"))
	}
	OpenLevelFromSoftObjectPtrAsync(levelRef);
}

void UHUDMainMenu::OpenLevelFromSoftObjectPtrAsync(TSoftObjectPtr<UWorld>& levelReference)
{
	if (levelReference.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("OpenLevelFromSoftObjectPtr: Level Reference Is Null"));
		return;
	}

	if (levelReference.IsValid())
	{

		FString levelPackageName = levelReference.GetLongPackageName();
		FString shortLevelName = FPackageName::GetShortName(levelPackageName);

		UGameplayStatics::OpenLevel(GetWorld(), FName(*shortLevelName));
		return;
	}

	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	FSoftObjectPath LevelPath = levelReference.ToSoftObjectPath();

	Streamable.RequestAsyncLoad(LevelPath, FStreamableDelegate::CreateUObject(this, &UHUDMainMenu::OpenLevelBySoftObject, levelReference));
}

void UHUDMainMenu::OpenLevelBySoftObject(TSoftObjectPtr<UWorld> LevelReference)
{
	if (!LevelReference.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("OpenLevelBySoftObject: Failed to load level asset."));
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("OpenLevelBySoftObject: Invalid World context."));
		return;
	}

	FString levelPackageName = LevelReference.GetLongPackageName();
	FString shortLevelName = FPackageName::GetShortName(levelPackageName);

	UE_LOG(LogTemp, Log, TEXT("Opening level: %s"), *shortLevelName);
	UGameplayStatics::OpenLevel(World, FName(*shortLevelName));
}