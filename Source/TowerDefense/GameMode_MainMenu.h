#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_MainMenu.generated.h"

class UHUDMainMenu;

UCLASS()
class TOWERDEFENSE_API AGameMode_MainMenu : public AGameModeBase
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
	TSoftObjectPtr<UWorld> GetLevelForMainMenu(int levelIndex);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> levelOne;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> levelTwo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> levelThree;

};
