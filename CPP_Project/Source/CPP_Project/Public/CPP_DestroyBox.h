// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CPP_DestroyBox.generated.h"

UCLASS()
class CPP_PROJECT_API ACPP_DestroyBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_DestroyBox();

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

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
