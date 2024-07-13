#include "PuzzlePlatformsGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.h"
#include "MenuWidget.h"
#include "Engine/Engine.h"
#include "InGameMenu.h" // 추가

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr))
	{
		UE_LOG(LogTemp, Error, TEXT("MenuBPClass not found!"));
		return;
	}

	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr))
	{
		UE_LOG(LogTemp, Error, TEXT("InGameMenuBPClass not found!"));
		return;
	}

	InGameMenuClass = InGameMenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr))
	{
		UE_LOG(LogTemp, Error, TEXT("Menu widget creation failed!"));
		return;
	}
	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 1.0f, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	World->ServerTravel("/Game/PuzzlePlatforms/Maps/ThirdPersonMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::InGameLoadMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;

	UInGameMenu* GameInstanceMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
	if (!ensure(GameInstanceMenu != nullptr)) return;

	GameInstanceMenu->Setup();
	GameInstanceMenu->SetMenuInterface(this); // 추가: MenuSystem 설정
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("Loading Main Menu"));
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/PuzzlePlatforms/Maps/MainMenu", TRAVEL_Absolute);
}
