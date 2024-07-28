// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Bullet.h"
#include "GameOverWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    // Box Component Create
    compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
    // Set First Component
    SetRootComponent(compBox);
    // Set Box Size
	compBox->SetBoxExtent(FVector(50,50,50));

	// Set Collision
	compBox->SetCollisionProfileName(TEXT("PlayerPreset"));
	
    // StaticMesh Component Create
    compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
    // Set child Component of Box Component
	compMesh->SetupAttachment(compBox);
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

	// Load Cube StaticMesh
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	
	// Load Success
	if (tempMesh.Succeeded())
	{
		// Input staticMesh data from tempMesh
		compMesh->SetStaticMesh(tempMesh.Object);
	}
	// Load Material
	ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	if (tempMat.Succeeded())
	{
		// Input compMesh data from tempMat
		compMesh->SetMaterial(0, tempMat.Object);
	}
	
	// Make Fire Position
	firePosition = CreateDefaultSubobject<USceneComponent>(TEXT("FIRE"));
	firePosition->SetupAttachment(compBox);
	firePosition->SetRelativeLocation(FVector(150,0,0));

	// Load Bullet Component
	ConstructorHelpers::FClassFinder<ABullet> tempBullet(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Bullet.BP_Bullet_C'"));
	if (tempBullet.Class)
	{
		bulletFactory = tempBullet.Class;
	}

	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("/Script/Engine.SoundWave'/Game/Sounds/one-shote-laser.one-shote-laser'"));
	if (tempSound.Succeeded())
	{
		fireSound = tempSound.Object;
	}

	// Load gameOverWidget
	ConstructorHelpers::FClassFinder<UGameOverWidget> tempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/BP_GameOverWidget.BP_GameOverWidget_C'"));
	if (tempWidget.Succeeded())
	{
		gameOverWidgetFactory = tempWidget.Class;
	}
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Set Axis
	FVector dirH = FVector::YAxisVector * this->h;
	FVector dirV = FVector::XAxisVector * this->v;
	FVector dir = dirH + dirV;
	
	// Axis to be normalize
	dir.Normalize();
	
	// move to Direction
	// P = P0 + vt  (v : dir * speed
	FVector p0 = GetActorLocation();
	FVector vt = dir * this->speed * DeltaTime;
	SetActorLocation(p0 + vt);

	// Fire Auto Logic
	currTime = currTime + DeltaTime;
	if (currTime > creaeteTime)
	{
		// InputFire();
		currTime = 0;
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set InputHorizonal
	PlayerInputComponent->BindAxis(TEXT("Horizontal"),this, &APlayerPawn::InputHorizonal);
	// Set InputVertical
	PlayerInputComponent->BindAxis(TEXT("Vertical"),this, &APlayerPawn::InputVertical);
	// Set InputFire
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerPawn::InputFire);
	
}

void APlayerPawn::InputHorizonal(float value)
{
	// UE_LOG(LogTemp, Warning, TEXT("H : %f"),  value)
	
	this->h = value;
}

void APlayerPawn::InputVertical(float value)
{
	// UE_LOG(LogTemp, Warning, TEXT("V : %f"),  value)
	this->v = value;
}

void APlayerPawn::InputFire()
{
	// Create Bullet
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation());
	// bullet->SetActorLocation(this->firePosition->GetComponentLocation());

	// Play fire Sound;
	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
}

void APlayerPawn::ShowGameOverUI()
{
	// create Widget
	gameOverUI = CreateWidget<UGameOverWidget>(GetWorld(), gameOverWidgetFactory);

	gameOverUI->AddToViewport();

	// show mouse controller
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}


