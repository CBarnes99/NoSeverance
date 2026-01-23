#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_MainMenu.generated.h"

class UHUDMainMenu;

UCLASS()
class NOSEVERANCE_API AGameMode_MainMenu : public AGameModeBase
{
	GENERATED_BODY()
	
public:

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UHUDMainMenu> mainMenuClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UHUDMainMenu* mainMenu;

	UFUNCTION(BlueprintCallable)
	void GetLevelForMainMenu(int levelIndex);

	UFUNCTION(BlueprintCallable)
	void LoadFromSaveData();

	UFUNCTION()
	void OpenLevelFromSoftObjectPtrAsync(TSoftObjectPtr<UWorld>& levelReference);
	
	UFUNCTION()
	void OpenLevelBySoftObject(TSoftObjectPtr<UWorld> LevelReference);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<int, TSoftObjectPtr<UWorld>> levels;

};
