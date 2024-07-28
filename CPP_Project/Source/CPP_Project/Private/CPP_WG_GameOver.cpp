// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_WG_GameOver.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"


void UCPP_WG_GameOver::NativeConstruct()
{
	Super::NativeConstruct();// 이거 왜함?

	BT_Start->OnClicked.AddDynamic(this, &UCPP_WG_GameOver::OnCustomRestart);
	BT_Exit->OnClicked.AddDynamic(this, &UCPP_WG_GameOver::OnCustomExit);

	this->PlayAnimation(MyAnim);
}

void UCPP_WG_GameOver::OnCustomExit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
}

void UCPP_WG_GameOver::OnCustomRestart()
{
	FString tempStr = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), FName(tempStr));
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
}
