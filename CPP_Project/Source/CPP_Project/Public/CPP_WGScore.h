// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_WGScore.generated.h"

/**
 * 
 */
UCLASS()
class CPP_PROJECT_API UCPP_WGScore : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UTextBlock *T_Score;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UTextBlock *T_HighScore;


	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UProgressBar *PB_HpBar;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UCPP_WG_GameOver *GameOverUI;

	void SetScore(int32 NewScore);

	void SetHighScore(int32 NewScore);

	void SetHpBar(float CurrHp, float MaxHp);

	void ShowGameOver();

};
