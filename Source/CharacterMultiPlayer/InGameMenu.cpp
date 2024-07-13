#include "InGameMenu.h"
#include "Components/Button.h"
#include "PuzzlePlatformsGameInstance.h" // 필요한 경우 추가

bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelPressed);

	if (!ensure(ExitButton != nullptr)) return false;
	ExitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitGame);

	return true;
}

void UInGameMenu::CancelPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Cancel Button Pressed"));
	Teardown();
}

void UInGameMenu::QuitGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Quit Button Pressed"));
	if (MenuSystem != nullptr)
	{
		Teardown();
		MenuSystem->LoadMainMenu();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MenuSystem is null!"));
	}
}
