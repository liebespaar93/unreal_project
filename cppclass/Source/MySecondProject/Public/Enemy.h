// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class MYSECONDPROJECT_API AEnemy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	// Box component
	UPROPERTY(EditAnywhere)
	class  UBoxComponent* compBox;
    
	// StaticMesh component
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compMesh;

	// Enemy speed
	float  speed = 100;
	
	// target point
	UPROPERTY(EditAnywhere)
	class AActor* target;
	
	FVector diraction;

	/**
	 * change move type
	 * @def default = 30
	 * @note tolerance value 0 ~ 100
	 */
	UPROPERTY(EditAnywhere)
	int32 traceRate;

	TSubclassOf<class ADestroyEffect> destroyEffect;
};
