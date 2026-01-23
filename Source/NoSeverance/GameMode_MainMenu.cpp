#include "GameMode_MainMenu.h"
#include "HUDMainMenu.h"
#include "Core_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Misc/PackageName.h"

void AGameMode_MainMenu::BeginPlay()
{
	Super::BeginPlay();

	mainMenu = CreateWidget<UHUDMainMenu>(GetWorld(), mainMenuClass);
	mainMenu->AddToViewport(0);

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	mainMenu->OpenLevelEvent.BindUObject(this, &AGameMode_MainMenu::GetLevelForMainMenu);
	LoadFromSaveData();
}

void AGameMode_MainMenu::LoadFromSaveData()
{
	UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UCore_GameInstance* coreGameInstance = Cast<UCore_GameInstance>(gameInstance);
	coreGameInstance->LoadGame();
}

void AGameMode_MainMenu::GetLevelForMainMenu(int levelIndex)
{
	if (!levels.Contains(levelIndex))
	{
		UE_LOG(LogTemp, Error, TEXT("GetLevelForMainMenu: No level with index - %d, Add level to map within - %s, returned null"), levelIndex, *this->GetName());
		return;
	}

	TSoftObjectPtr<UWorld>* levelPtr = levels.Find(levelIndex);

	if (!levelPtr)
	{
		UE_LOG(LogTemp, Error, TEXT("GetLevelForMainMenu: Level index %d not found in levels map"), levelIndex);
		return;
	}

	TSoftObjectPtr<UWorld> levelRef = *levelPtr;
	OpenLevelFromSoftObjectPtrAsync(levelRef);
}

void AGameMode_MainMenu::OpenLevelFromSoftObjectPtrAsync(TSoftObjectPtr<UWorld>& levelReference)
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

	Streamable.RequestAsyncLoad(LevelPath, FStreamableDelegate::CreateUObject(this, &AGameMode_MainMenu::OpenLevelBySoftObject, levelReference));
}

void AGameMode_MainMenu::OpenLevelBySoftObject(TSoftObjectPtr<UWorld> LevelReference)
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