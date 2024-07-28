// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "CPP_WG_Hp.h"
#include "CPP_Enemy.generated.h"

UCLASS()
class CPP_PROJECT_API ACPP_Enemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Enemy();
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* ExplosionVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TargetActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 300;
	FVector dir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave *DestroySound;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void MakeDir();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent *WidgetComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCPP_WG_Hp *WidgetHp;

	int32 Hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp = 3;

};
