// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "CPP_Player.generated.h"

UCLASS()
class CPP_PROJECT_API ACPP_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_Player();


	float HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP = 3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent *BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComp;

	UArrowComponent* ArrowComp;

	USoundWave* FireSound;

	// Bullet Create
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACPP_Bullet> bulletFactory;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 500;

	float Vertical = 0;
	float Horizontal = 0;

	void InputMovementControl(UInputComponent* PlayerInputComponent);
	void InputVertical(float value);
	void InputHorizontal(float value);
	void InputFire();


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* ExplosionVFX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave *DestroySound;

	void OnTakeDamage(float damage);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxBullets = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class ACPP_Bullet *> bullets;

};
