// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "CPP_WG_Hp.generated.h"

/**
 * 
 */
UCLASS()
class CPP_PROJECT_API UCPP_WG_Hp : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar *PB_HpBar;

	void SetHpBar(float hp, float maxHp);
};
