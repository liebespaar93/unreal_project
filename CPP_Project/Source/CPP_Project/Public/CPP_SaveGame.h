// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CPP_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CPP_PROJECT_API UCPP_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HighScoreSave;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString MySlotName = TEXT("HighScore");

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MyUserIndex = 0;
};
