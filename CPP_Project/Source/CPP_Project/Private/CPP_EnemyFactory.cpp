// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_EnemyFactory.h"
#include "CPP_Enemy.h"
#include <CPP_GameMode.h>

// Sets default values
ACPP_EnemyFactory::ACPP_EnemyFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->ArrowComp = CreateDefaultSubobject<UArrowComponent>(FName("ArrowComp"));
}

// Called when the game starts or when spawned
void ACPP_EnemyFactory::BeginPlay()
{
	Super::BeginPlay();
	
	ACPP_GameMode* gameMode = Cast<ACPP_GameMode>(GetWorld()->GetAuthGameMode());
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &ACPP_EnemyFactory::MakeEnemy, DelayTime, true);
}
void ACPP_EnemyFactory::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(Handle);
}

// Called every frame
void ACPP_EnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->CurrTime > this->DelayTime)
	{
		this->CurrTime = 0;
		UE_LOG(LogTemp, Warning, TEXT("CurrTime : ??"));
		MakeEnemy();
	}
	this->CurrTime += DeltaTime;
}

void ACPP_EnemyFactory::MakeEnemy()
{
	GetWorld()->SpawnActor<ACPP_Enemy>(this->EnemyFactory, ArrowComp->GetComponentLocation(), ArrowComp->GetComponentRotation());
}

