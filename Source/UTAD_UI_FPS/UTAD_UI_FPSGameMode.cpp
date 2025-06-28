// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTAD_UI_FPSGameMode.h"
#include "UTAD_UI_FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUTAD_UI_FPSGameMode::AUTAD_UI_FPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
