#pragma once

#include "CoreMinimal.h"
#include "MainMenu.h"
#include "Engine/GameInstance.h"
#include "MenuSystem.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 *
 */
UCLASS()
class CHARACTERMULTIPLAYER_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuSystem
{
	GENERATED_BODY()

public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	UFUNCTION(Exec)
	virtual void Host() override;

	UFUNCTION(Exec)
	virtual void Join(const FString& Address) override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void InGameLoadMenu();

	virtual void LoadMainMenu() override;

private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu* Menu;
};
