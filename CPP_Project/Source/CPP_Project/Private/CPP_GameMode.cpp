// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GameMode.h"
#include "CPP_WG_GameOver.h"
#include <Kismet/GameplayStatics.h>
#include <CPP_SaveGame.h>

void ACPP_GameMode::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySound2D(GetWorld(), BGSound);

	ScoreUI = Cast<UCPP_WGScore>(CreateWidget(GetWorld(), MainUIFactory));
	ScoreUI->AddToViewport();
}

void ACPP_GameMode::AddScore(int point)
{
	this->score += point;
	this->ScoreUI->SetScore(this->score);
	FString str = FString::Printf( TEXT( "Score : %d"), this->score);
	GEngine->AddOnScreenDebugMessage(0, 3, FColor::Green, str);
	if (this->score > this->highScore)
	{
		this->highScore = this->score;
		this->ScoreUI->SetHighScore(this->highScore);
	}
}

void ACPP_GameMode::SetHpUI(float hp, float maxHp)
{
	this->ScoreUI->SetHpBar(hp, maxHp);
}

void ACPP_GameMode::ViewGameOverUI()
{
	this->ScoreUI->ShowGameOver();
}

void ACPP_GameMode::MySaveGame()
{
	UCPP_SaveGame *saveGame = Cast<UCPP_SaveGame>(UGameplayStatics::CreateSaveGameObject(UCPP_SaveGame::StaticClass()));
	
	saveGame->HighScoreSave = this->highScore;

	UGameplayStatics::SaveGameToSlot(saveGame, this->MySlotName, this->MyUserIndex);
}

int32 ACPP_GameMode::MyLoadGame()
{
	bool isExist = UGameplayStatics::DoesSaveGameExist(MySlotName, MyUserIndex);
	if (isExist)
	{
		UCPP_SaveGame* saveGame = Cast<UCPP_SaveGame>(UGameplayStatics::CreateSaveGameObject(UCPP_SaveGame::StaticClass()));
		if (nullptr != saveGame)
		{
			return saveGame->HighScoreSave;
		}
	}
	return 0;
}
