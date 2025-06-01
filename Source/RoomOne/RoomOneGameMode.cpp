// Copyright Epic Games, Inc. All Rights Reserved.

#include "RoomOneGameMode.h"
#include "RoomOneCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARoomOneGameMode::ARoomOneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
