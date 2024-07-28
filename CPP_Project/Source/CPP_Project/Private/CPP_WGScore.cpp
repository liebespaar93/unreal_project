// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_WGScore.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "CPP_WG_GameOver.h"

void UCPP_WGScore::NativeConstruct()
{
 	Super::NativeConstruct();// 이거 왜함?
 	this->GameOverUI->SetVisibility(ESlateVisibility::Hidden);	
}

void UCPP_WGScore::SetScore(int32 NewScore)
{
	this->T_Score->SetText(FText::AsNumber(NewScore));

}

void UCPP_WGScore::SetHighScore(int32 NewScore)
{
	this->T_HighScore->SetText(FText::AsNumber(NewScore));
}

void UCPP_WGScore::SetHpBar(float CurrHp, float MaxHp)
{
	this->PB_HpBar->SetPercent(CurrHp/MaxHp);
}

void UCPP_WGScore::ShowGameOver()
{
	this->GameOverUI->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}
