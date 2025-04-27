// Copyright Epic Games, Inc. All Rights Reserved.

#include "UCefViewPlaygroundGameMode.h"
#include "UCefViewPlaygroundCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUCefViewPlaygroundGameMode::AUCefViewPlaygroundGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_MainCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
