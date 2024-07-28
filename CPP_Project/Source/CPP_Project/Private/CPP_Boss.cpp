// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Boss.h"
#include "CPP_Bullet.h"
#include "CPP_Player.h"
#include "CPP_GameMode.h"
#include "CPP_WG_Hp.h"

#include <Kismet/GameplayStatics.h>

// Sets default values
ACPP_Boss::ACPP_Boss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/ShootingGame/Assets/Drone/Drone_low.Drone_low'"));
	ConstructorHelpers::FObjectFinder<UMaterial> TempMat(TEXT("/Script/Engine.Material'/Game/ShootingGame/Assets/Drone/Material__24.Material__24'"));
	ConstructorHelpers::FObjectFinder<USoundWave> TempSound(TEXT("/Script/Engine.SoundWave'/Game/ShootingGame/Assets/Sounds/Audio_Explosion.Audio_Explosion'"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem> TempVFX(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	BoxComp = CreateDefaultSubobject<UBoxComponent>(FName("BoxComp"));
	BoxComp->SetBoxExtent(FVector(100, 100, 100));
	SetRootComponent(BoxComp);

	// Make Mesh
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);
	MeshComp->SetRelativeRotation(FRotator(0,90,0));
	MeshComp->SetRelativeScale3D(FVector(2,2,2));

	// Create Widget
	this->WidgetComp = CreateDefaultSubobject<UWidgetComponent>(FName("WidgetComp"));
	this->WidgetComp->SetupAttachment(this->BoxComp);
	this->WidgetComp->SetRelativeLocation(FVector(200, 0, 0));
	this->WidgetComp->SetRelativeRotation(FRotator(0, 90, 0));
	this->WidgetComp->SetDrawSize(FVector2D(350, 40));
	
	if (TempMesh.Succeeded())
		MeshComp->SetStaticMesh(TempMesh.Object);
	if (TempMat.Succeeded())
		MeshComp->SetMaterial(0, TempMat.Object);
	if (TempSound.Succeeded())
		DestroySound = TempSound.Object;
// 	if (TempVFX.Succeeded())
// 		ExplosionVFX = TempVFX.Object;

	BoxComp->SetCollisionProfileName(FName("Enemy"));
	MeshComp->SetCollisionProfileName(FName("NoCollision"));

	this->Hp = this->MaxHp;
}

// Called when the game starts or when spawned
void ACPP_Boss::BeginPlay()
{
	Super::BeginPlay();

	this->WidgetHp = Cast<UCPP_WG_Hp>(this->WidgetComp->GetWidget());
 	this->WidgetHp->SetHpBar(this->Hp, this->MaxHp);
}

// Called every frame
void ACPP_Boss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	this->CurrTime += DeltaTime;
	float angle = 30;
	if (this->CurrTime > this->DelayTime)
	{
		this->CurrTime = 0;
		for (int rot = -180; rot < 360; rot += angle)
		{
			this->SetActorRotation(this->GetActorRotation() + FRotator(0, rot, 0));
			this->FireBullet();
		}
		this->SetActorRotation(FRotator(0, -180, 0));

	}
}

void ACPP_Boss::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA<ACPP_Bullet>())
	{
		ACPP_Bullet* bullet = Cast<ACPP_Bullet>(OtherActor);
		this->Hp -= 1;
		this->WidgetHp->SetHpBar(this->Hp, this->MaxHp);
		if (this->Hp <= 0)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), this->DestroySound);
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				this->ExplosionVFX,
				this->GetActorTransform()
			);
			this->Destroy();
		}
	}
}

void ACPP_Boss::FireBullet()
{
	GetWorld()->SpawnActor<ACPP_BossBullet>(this->BulletFactory, this->GetActorLocation() + this->GetActorForwardVector(), this->GetActorForwardVector().ToOrientationRotator());
}

