// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyEffect.generated.h"

UCLASS()
class MYSECONDPROJECT_API ADestroyEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sound Destroy
	UPROPERTY(EditAnywhere)
	class USoundBase* destroySound;
	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* destroyParticle;
	
	void DestroyEnemy();
};
