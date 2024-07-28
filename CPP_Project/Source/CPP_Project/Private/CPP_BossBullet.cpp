// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BossBullet.h"

// Sets default values
ACPP_BossBullet::ACPP_BossBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	ConstructorHelpers::FObjectFinder<UMaterial> TempMat(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	// Make Box Component & Setting

	BoxComp = CreateDefaultSubobject<UBoxComponent>(FName("BoxComp"));
	BoxComp->SetBoxExtent(FVector(50, 50, 50));
	SetRootComponent(BoxComp);

	BoxComp->SetWorldScale3D(FVector(1.0, 0.3, 0.3));
	// Make Mesh
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComp"));

	MeshComp->SetupAttachment(BoxComp);

	if (TempMesh.Succeeded())
		MeshComp->SetStaticMesh(TempMesh.Object);
	if (TempMat.Succeeded())
		MeshComp->SetMaterial(0, TempMat.Object);

}

// Called when the game starts or when spawned
void ACPP_BossBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_BossBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->SetActorLocation(this->GetActorLocation() + (this->GetActorForwardVector() * this->Speed * DeltaTime));
}

