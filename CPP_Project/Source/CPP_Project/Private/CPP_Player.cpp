// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Player.h"
#include "CPP_Bullet.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include <Kismet/GameplayStatics.h>
#include <CPP_GameMode.h>
// Sets default values
ACPP_Player::ACPP_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/ShootingGame/Assets/SpaceShip/Spaceship_ARA.Spaceship_ARA'"));
	ConstructorHelpers::FObjectFinder<UMaterial> TempMat(TEXT("/Script/Engine.Material'/Game/ShootingGame/Assets/SpaceShip/UV.UV'"));
	ConstructorHelpers::FObjectFinder<USoundWave> TempFire(TEXT("/Script/Engine.SoundWave'/Game/ShootingGame/Assets/Sounds/Audio_Bullet.Audio_Bullet'"));
	ConstructorHelpers::FObjectFinder<USoundWave> TempSound(TEXT("/Script/Engine.SoundWave'/Game/ShootingGame/Assets/Sounds/Audio_Explosion.Audio_Explosion'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> TempVFX(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));

	// Make Box Component & Setting

	BoxComp = CreateDefaultSubobject<UBoxComponent>(FName("BoxComp"));
	BoxComp->SetBoxExtent(FVector(50, 50, 50));
	SetRootComponent(BoxComp);

	// Make Mesh
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComp"));

	MeshComp->SetupAttachment(BoxComp);

	if (TempMesh.Succeeded())
		MeshComp->SetStaticMesh(TempMesh.Object);
	if (TempMat.Succeeded())
		MeshComp->SetMaterial(0, TempMat.Object);
	if (TempSound.Succeeded())
		DestroySound = TempSound.Object;
	if (TempVFX.Succeeded())
		ExplosionVFX = TempVFX.Object;

	// Create Arrow Comp
	ArrowComp = CreateDefaultSubobject<UArrowComponent>(FName("ArrowComp"));
	ArrowComp->SetRelativeLocation(FVector(100, 0,0));
	ArrowComp->SetupAttachment(BoxComp);


	// Set Sound
	if (TempFire.Succeeded())
		this->FireSound = TempFire.Object;

}

// Called when the game starts or when spawned
void ACPP_Player::BeginPlay()
{
	Super::BeginPlay();
	
	this->HP = this->MaxHP;
	ACPP_GameMode* gm = Cast<ACPP_GameMode>(GetWorld()->GetAuthGameMode());
	gm->SetHpUI(this->HP, this->MaxHP);


	for (int i = 0; i < 10; i++)
	{
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ACPP_Bullet* bullet = GetWorld()->SpawnActor<ACPP_Bullet>(this->bulletFactory);
		bullet->SetActiveBullet(false);
		this->bullets.Add(bullet);
	}
}

// Called every frame
void ACPP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector dir = FVector(this->Vertical, this->Horizontal, 0);
	dir.Normalize();


	this->SetActorLocation(this->GetTargetLocation() + (dir * this->Speed * DeltaTime));
}

// Called to bind functionality to input
void ACPP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	this->InputMovementControl(PlayerInputComponent);
	PlayerInputComponent->BindAction(FName("Fire"), IE_Pressed, this, &ACPP_Player::InputFire);
}

void ACPP_Player::InputMovementControl(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(FName("Vertical"), this, &ACPP_Player::InputVertical);
	PlayerInputComponent->BindAxis(FName("Horizontal"), this, &ACPP_Player::InputHorizontal);
}

void ACPP_Player::InputVertical(float value)
{
	this->Vertical = value;
}

void ACPP_Player::InputHorizontal(float value)
{
	this->Horizontal = value;
}

void ACPP_Player::InputFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire"));

	// ACPP_Bullet *test =  GetWorld()->SpawnActor<ACPP_Bullet>(bulletFactory, ArrowComp->GetComponentLocation(), ArrowComp->GetComponentRotation());

	// SoundPlay
	UGameplayStatics::PlaySound2D(GetWorld(), this->FireSound);
	
	for (ACPP_Bullet *bullet : this->bullets)
	{ 
		if (bullet->MeshComp->IsVisible())
			continue;
		bullet->SetActorLocation(this->GetActorLocation());
		bullet->SetActiveBullet(true);
		break;
	}
}

void ACPP_Player::OnTakeDamage(float damage)
{
	if (damage < 0)
		return;
	this->HP -= damage;
	ACPP_GameMode* gm = Cast<ACPP_GameMode>(GetWorld()->GetAuthGameMode());
	gm->SetHpUI(this->HP, this->MaxHP);

	if (HP <= 0)
	{

		UGameplayStatics::PlaySound2D(GetWorld(), this->DestroySound);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), this->ExplosionVFX, this->GetActorTransform());
		this->Destroy();
		gm->ViewGameOverUI();

	}
}



