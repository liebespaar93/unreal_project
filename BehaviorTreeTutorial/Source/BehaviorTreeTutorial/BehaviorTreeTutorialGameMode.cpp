// Copyright Epic Games, Inc. All Rights Reserved.

#include "BehaviorTreeTutorialGameMode.h"
#include "BehaviorTreeTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABehaviorTreeTutorialGameMode::ABehaviorTreeTutorialGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
