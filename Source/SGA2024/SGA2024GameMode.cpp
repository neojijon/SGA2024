// Copyright Epic Games, Inc. All Rights Reserved.

#include "SGA2024GameMode.h"
#include "SGA2024Character.h"
#include "UObject/ConstructorHelpers.h"

ASGA2024GameMode::ASGA2024GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> MyPlayerControllerClass(TEXT("/Game/ThirdPerson/Blueprints/BP_PlayerControll"));
	
	if (MyPlayerControllerClass.Class != NULL)
	{
		PlayerControllerClass = MyPlayerControllerClass.Class;
	}
}
