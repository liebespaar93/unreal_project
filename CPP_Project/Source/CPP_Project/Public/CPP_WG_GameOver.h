// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_WG_GameOver.generated.h"

/**
 * @brif 종료 및 다시시작
 * 이벤트 드리븐 바인딩하는걸 칭한다
 * 
 */
UCLASS()
class CPP_PROJECT_API UCPP_WG_GameOver : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton *BT_Start;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton *BT_Exit;
	
	UPROPERTY(EditAnywhere, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* MyAnim;

	UFUNCTION()
	void OnCustomRestart();

	UFUNCTION()
	void OnCustomExit();
};
