// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYSECONDPROJECT_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual  void NativeConstruct() override;
	
	// restart button
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* btnRestart;
		
	// end button
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* btnQuit;

	// Press Restart Button Function
	UFUNCTION()
	void Restart();

	// Press Quit Button Funcion
	UFUNCTION()
	void Quit();
};
