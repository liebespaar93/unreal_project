// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

#include "Enemy.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set Enemy Factory
	ConstructorHelpers::FClassFinder<AEnemy> tempEnemy(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Enemy.BP_Enemy_C'"));
	if (tempEnemy.Succeeded())
	{
		this->enemyFactory = tempEnemy.Class;
	}
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Time Increase 
	currTime += DeltaTime;

	// if Time over then create time
	if (currTime > createTime)
	{
		// Create Enemy
		GetWorld()->SpawnActor<AEnemy>(enemyFactory, GetActorLocation(), GetActorRotation());
		// reset Time
		currTime = 0;
	}
}

