#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenu.generated.h"

/**
 *
 */
UCLASS()
class CHARACTERMULTIPLAYER_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()
protected:
	virtual bool Initialize() override;
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

	UFUNCTION()
	void CancelPressed();

	UFUNCTION()
	void QuitGame();
};
