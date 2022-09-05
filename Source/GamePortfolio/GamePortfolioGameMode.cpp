// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamePortfolioGameMode.h"
#include "GamePortfolioCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGamePortfolioGameMode::AGamePortfolioGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
