// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Enemy.h"
#include "CPP_Bullet.h"
#include "CPP_Player.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include <Kismet/GameplayStatics.h>
#include "CPP_GameMode.h"

// Sets default values
ACPP_Enemy::ACPP_Enemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/ShootingGame/Assets/Drone/Drone_low.Drone_low'"));
	ConstructorHelpers::FObjectFinder<UMaterial> TempMat(TEXT("/Script/Engine.Material'/Game/ShootingGame/Assets/Drone/Material__24.Material__24'"));
	ConstructorHelpers::FObjectFinder<USoundWave> TempSound(TEXT("/Script/Engine.SoundWave'/Game/ShootingGame/Assets/Sounds/Audio_Explosion.Audio_Explosion'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> TempVFX(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	// Make Box Component & Setting

	BoxComp = CreateDefaultSubobject<UBoxComponent>(FName("BoxComp"));
	BoxComp->SetBoxExtent(FVector(50, 50, 50));
	SetRootComponent(BoxComp);


	// Make Mesh
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComp"));

	MeshComp->SetupAttachment(BoxComp);
	MeshComp->SetRelativeRotation(FRotator(0, 90, 0));

	// Create Widget
	this->WidgetComp = CreateDefaultSubobject<UWidgetComponent>(FName("WidgetComp"));
	this->WidgetComp->SetupAttachment(this->BoxComp);
	this->WidgetComp->SetRelativeLocation(FVector(100, 0, 0));
	this->WidgetComp->SetRelativeRotation(FRotator(0, 90, 0));
	this->WidgetComp->SetDrawSize(FVector2D(150, 30));

	if (TempMesh.Succeeded())
		MeshComp->SetStaticMesh(TempMesh.Object);
	if (TempMat.Succeeded())
		MeshComp->SetMaterial(0, TempMat.Object);
	if (TempSound.Succeeded())
		DestroySound = TempSound.Object;
	if (TempVFX.Succeeded())
		ExplosionVFX = TempVFX.Object;

	BoxComp->SetCollisionProfileName(FName("Enemy"));
	MeshComp->SetCollisionProfileName(FName("NoCollision"));


	this->Hp = this->MaxHp;
}

// Called when the game starts or when spawned
void ACPP_Enemy::BeginPlay()
{
	Super::BeginPlay();

	this->MakeDir();

	this->WidgetHp = Cast<UCPP_WG_Hp>(this->WidgetComp->GetWidget());

	this->WidgetHp->SetHpBar(this->Hp,this->MaxHp);
}

// Called every frame
void ACPP_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->SetActorLocation(this->GetActorLocation() + this->dir * DeltaTime * this->Speed);
}
void ACPP_Enemy::MakeDir()
{
	if (!GetWorld()->GetFirstPlayerController()->GetPawn())
		return;
	this->TargetActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	this->dir = this->TargetActor->GetActorLocation() - this->GetActorLocation();
	this->dir.Normalize();
}

void ACPP_Enemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	UGameplayStatics::PlaySound2D(GetWorld(), this->DestroySound);
	if (OtherActor->IsA<ACPP_Bullet>())
	{
		ACPP_GameMode* gm = Cast<ACPP_GameMode>(GetWorld()->GetAuthGameMode());
		gm->AddScore(1);

		UGameplayStatics::PlaySound2D(GetWorld(), this->DestroySound);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), this->ExplosionVFX, this->GetActorTransform());
		Cast<ACPP_Bullet>(OtherActor)->SetActiveBullet(false);
		this->Hp -= 1;
		this->WidgetHp->SetHpBar(this->Hp , this->MaxHp);
		if (this->Hp <= 0)
			this->Destroy();
	}
	if (OtherActor->IsA<ACPP_Player>())
	{
		ACPP_Player * player = Cast<ACPP_Player>(OtherActor);
		player->OnTakeDamage(this->Damage);

		UGameplayStatics::PlaySound2D(GetWorld(), this->DestroySound);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), this->ExplosionVFX, this->GetActorTransform());
		this->Destroy();
	}
}