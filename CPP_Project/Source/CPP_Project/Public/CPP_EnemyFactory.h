// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"

#include "CPP_EnemyFactory.generated.h"

UCLASS()
class CPP_PROJECT_API ACPP_EnemyFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_EnemyFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACPP_Enemy> EnemyFactory;

	void MakeEnemy();
	
	UPROPERTY(EditAnywhere)
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere)
	UArrowComponent* ArrowComp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DelayTime = 3;

	float CurrTime = 0;

	FTimerHandle Handle;
};
