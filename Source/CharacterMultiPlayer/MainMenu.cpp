#include "MainMenu.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	// Setup
	if (!ensure(Host != nullptr)) return false;
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(Join != nullptr)) return false;
	Join->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(Back != nullptr)) return false;
	Back->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(JoinGameButton != nullptr)) return false;
	JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(ExitButton != nullptr)) return false;
	ExitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitPressed);

	return true;
}

void UMainMenu::HostServer()
{
	if (MenuSystem != nullptr)
	{
		MenuSystem->Host();
	}
}

void UMainMenu::JoinServer()
{
	if (MenuSystem != nullptr)
	{
		if (!ensure(IPText != nullptr)) return;
		const FString Adress = IPText->GetText().ToString();
		MenuSystem->Join(Adress);
	}
}


void UMainMenu::OpenJoinMenu()
{
	MenuSwitcher->SetActiveWidgetIndex(1);
}

void UMainMenu::OpenMainMenu()
{
	MenuSwitcher->SetActiveWidgetIndex(0);
}

void UMainMenu::QuitPressed()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}
