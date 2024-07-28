// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "CPP_WG_Hp.h"
#include "CPP_BossBullet.h"
#include "CPP_Boss.generated.h"

UCLASS()
class CPP_PROJECT_API ACPP_Boss : public AActor
{
	GENERATED_BODY()
	
public:

	enum EnumBossState
	{
		
	};
	// Sets default values for this actor's properties
	ACPP_Boss();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent *BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* ExplosionVFX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TargetActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave *DestroySound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent *WidgetComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widget")
	UCPP_WG_Hp *WidgetHp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACPP_BossBullet> BulletFactory;

	int32 Hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp = 10;



	float CurrTime = 0;
	float DelayTime = 3;

	void FireBullet();
};
