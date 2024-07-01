// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterMultiPlayerGameMode.h"
#include "CharacterMultiPlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACharacterMultiPlayerGameMode::ACharacterMultiPlayerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
