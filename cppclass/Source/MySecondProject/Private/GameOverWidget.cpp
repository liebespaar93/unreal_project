// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void  UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btnRestart->OnClicked.AddDynamic(this, &UGameOverWidget::Restart);
	btnQuit->OnClicked.AddDynamic(this, &UGameOverWidget::Quit);
}

void UGameOverWidget::Restart()
{
	// reload Level
	UGameplayStatics::OpenLevel(GetWorld(),TEXT("ShootingMap"));
	
}

void UGameOverWidget::Quit()
{
	// Quit Game
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
	
}