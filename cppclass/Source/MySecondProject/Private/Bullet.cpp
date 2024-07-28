// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"

#include "Components/BoxComponent.h"

// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	SetRootComponent(compBox);
	compBox->SetBoxExtent(FVector(50,50,50));
	compBox->SetWorldScale3D(FVector(1.0,0.2,0.2));

	compBox->SetCollisionObjectType(ECC_GameTraceChannel1);
	compBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	compBox->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);
	
	
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	compMesh->SetupAttachment(compBox);
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}
	ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Engine/MapTemplates/Materials/BasicAsset03.BasicAsset03'"));
	
	if (tempMat.Succeeded())
	{
		compMesh->SetMaterial(0,tempMat.Object);
	}
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(1);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Move Bullet
	FVector p0 = this->GetActorLocation();
	FVector vt = FVector::XAxisVector * speed * DeltaTime;
	this->SetActorLocation(p0 + vt);
}

