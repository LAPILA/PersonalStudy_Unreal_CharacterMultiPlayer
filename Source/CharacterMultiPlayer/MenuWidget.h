
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem.h"
#include "MenuWidget.generated.h"

/**
 *
 */
UCLASS()
class CHARACTERMULTIPLAYER_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Setup();
	void Teardown();

	void SetMenuInterface(IMenuSystem* MenuSystem);

protected:
	IMenuSystem* MenuSystem;
};