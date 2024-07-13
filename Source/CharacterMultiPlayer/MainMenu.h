#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

/**
 *
 */
UCLASS()
class CHARACTERMULTIPLAYER_API UMainMenu : public UMenuWidget 
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* Join;

	UPROPERTY(meta = (BindWidget))
	class UButton* Back;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinGameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;
	
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPText;
	
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();
	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void QuitPressed();
};
