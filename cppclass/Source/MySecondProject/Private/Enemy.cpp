// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy.h"

#include "DestroyEffect.h"
#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set TraceRate default
	traceRate = 30;
	
	// Box Component Create
	compBox  =  CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	// Set First Component
	SetRootComponent(compBox);
	// Set Box Size
	compBox->SetBoxExtent(FVector(50,50,50));

	// Set Collision
	compBox->SetCollisionObjectType(ECC_GameTraceChannel3);
	compBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	compBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	compBox->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	
	// StaticMesh Component Create
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	// Set child Component of Box Component
	compMesh->SetupAttachment(compBox);

	// Set Collision None
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));
	
	// Load Cube StaticMesh
	ConstructorHelpers::FObjectFinder<UStaticMesh>  tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));	
	// Load Success
	if  (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}
	// Load Material
	ConstructorHelpers::FObjectFinder<UMaterial>  tempMat(TEXT("/Script/Engine.Material'/Engine/MapTemplates/Materials/BasicAsset01.BasicAsset01'"));

	if (tempMat.Succeeded())
	{
		compMesh->SetMaterial(0, tempMat.Object);
	}

	// Load Destroy
	ConstructorHelpers::FClassFinder<ADestroyEffect>  tempDestroy(TEXT("/Script/CoreUObject.Class'/Script/MySecondProject.DestroyEffect'"));
	if (tempDestroy.Succeeded())
	{
		destroyEffect = tempDestroy.Class;
	}

	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// 1 - 100 Random value
	int32 rand = FMath::RandRange(1,100);
	
	if (rand > this->traceRate)
	{
		// Get Player position
		target = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());

		if (target != nullptr)
		{
			// direction move point
			diraction = target->GetActorLocation() - this->GetActorLocation();
			// normalize vector
			diraction.Normalize();
		}
		else
		{
			diraction = FVector::BackwardVector;
		}
	}
	else
	{
		diraction = FVector::BackwardVector;
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// player Move point
	// player_position + move Point
	FVector p0 = GetActorLocation();
	FVector v1 = diraction * speed * DeltaTime;
	
	this->SetActorLocation(p0 + v1);
}

/**
 * 
 * @param OtherActor 붙이친 엑터정보
 */
void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// call parents NotifyActorBeginOverlap
	Super::NotifyActorBeginOverlap(OtherActor);

	// UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());

	// if collide player make GameOver UI
	if (OtherActor->GetName().Contains(TEXT("Player")))
	{
		// Show GameOver UI
		APlayerPawn *player = Cast<APlayerPawn>(OtherActor);
		player->ShowGameOverUI();
	}

	GetWorld()->SpawnActor<ADestroyEffect>(destroyEffect, GetActorLocation(), GetActorRotation());
	
	// destroy both
	OtherActor->Destroy();
	this->Destroy();
}