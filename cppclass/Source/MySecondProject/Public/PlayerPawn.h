// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class MYSECONDPROJECT_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    // Box component
    UPROPERTY(EditAnywhere)
    class  UBoxComponent* compBox;
    
    // StaticMesh component
    UPROPERTY(EditAnywhere)
    class UStaticMeshComponent* compMesh;

	// Bullet Create Postion
	UPROPERTY(EditAnywhere)
	class USceneComponent* firePosition;

	// Bullet
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> bulletFactory;

	// Sound
	UPROPERTY(EditAnywhere)
	class USoundBase* fireSound;

	// Game Over Widget
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameOverWidget> gameOverWidgetFactory;
	
	// Game Over variable
	class UGameOverWidget* gameOverUI;
	
	// Horizonal & Vertical value;
	float h;
	float v;
	float speed = 200;

	// Auto Fire
	float currTime = 0;
	UPROPERTY(EditAnywhere)
	float creaeteTime = 1;

	
	// A, D Key bind 
	void InputHorizonal(float value);
	// W, S Key bind
	void InputVertical(float value);
	// space Key bind
	void InputFire();

	// Show GameOver Widget 
	void ShowGameOverUI();
	
};
