// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "CPP_WGScore.h"
#include "CPP_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPP_PROJECT_API ACPP_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	enum LevelMode
	{
		Boss,
		Standard
	};

	UPROPERTY(EditAnywhere)
	USoundWave* BGSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainUIFactory;

	 UCPP_WGScore* ScoreUI;

	 int score = 0;
	 UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 int highScore = 0;

	 // 저장을 위한 데이터 네이밍

	 FString MySlotName = "HighScore";
	 int32 MyUserIndex = 0;
	 LevelMode EnumLevelMode = Standard; 
public:
	void AddScore(int score);
	void SetHpUI(float hp, float maxHp);
	void ViewGameOverUI();

	void MySaveGame();
	int32 MyLoadGame();
};
