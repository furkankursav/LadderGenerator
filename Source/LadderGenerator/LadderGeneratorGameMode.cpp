// Copyright Epic Games, Inc. All Rights Reserved.

#include "LadderGeneratorGameMode.h"
#include "LadderGeneratorHUD.h"
#include "LadderGeneratorCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALadderGeneratorGameMode::ALadderGeneratorGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ALadderGeneratorHUD::StaticClass();
}
