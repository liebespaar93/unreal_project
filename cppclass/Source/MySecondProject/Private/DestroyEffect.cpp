// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyEffect.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ADestroyEffect::ADestroyEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Destroy Sound
	destroySound = CreateDefaultSubobject<USoundBase>(TEXT("SOUND"));
	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("/Script/Engine.SoundWave'/Engine/VREditor/Sounds/UI/Teleport_Committed.Teleport_Committed'"));
	
	if (tempSound.Succeeded())
	{
		destroySound = tempSound.Object;
	}

	// Destroy Particle
	destroyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> tempParticle(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	destroyParticle->SetAutoActivate(false);
	if (tempParticle.Succeeded())
	{
		// UE_LOG(LogTemp, Warning, TEXT("%s"), TEXT("Succeed Load"));
		destroyParticle->SetTemplate(tempParticle.Object);
	}
}

// Called when the game starts or when spawned
void ADestroyEffect::BeginPlay()
{
	Super::BeginPlay();

	DestroyEnemy();
}

// Called every frame
void ADestroyEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADestroyEffect::DestroyEnemy()
{
	// Sound & Effect
	UGameplayStatics::PlaySound2D(GetWorld(), destroySound);
	// UGameplayStatics::PlaySoundAtLocation(this, destroySound, destroyParticle->GetComponentLocation());
	destroyParticle->Activate();
	this->SetLifeSpan(3);
}