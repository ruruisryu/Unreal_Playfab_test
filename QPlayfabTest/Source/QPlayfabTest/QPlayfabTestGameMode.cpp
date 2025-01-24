// Copyright Epic Games, Inc. All Rights Reserved.

#include "QPlayfabTestGameMode.h"
#include "QPlayfabTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AQPlayfabTestGameMode::AQPlayfabTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
