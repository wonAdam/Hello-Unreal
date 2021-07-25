// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	ExplosionFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionFX"));
	ExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ExplosionSound"));

	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ParticleSystem->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CapsuleCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	fBurstDelay = 0.0f;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	TotalTime = 0.0f;
	FiringCoolTime = 0.0f;
	bHit = false;
	bDestroy = false;
	bSpawnedPickup = false;
	fDestroyTimer = 1.0f;

	ExplosionFX->Deactivate();
	ExplosionSound->Deactivate();

	RandomStart = FMath::Rand();

	OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

void AEnemy::OnBeginOverlap(AActor* EnemyActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Bounds"))
	{
		bDestroy = true;
	}

	if (OtherActor->ActorHasTag("Asteroid") || OtherActor->ActorHasTag("Player"))
	{
		bHit = true;
	}

	if (OtherActor->ActorHasTag("Projectile"))
	{
		bHit = true;
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProcessTranslation(DeltaTime);

	ProcessFiring(DeltaTime);

	ProcessDestruction(DeltaTime);
}

void AEnemy::ProcessDestruction(float DeltaTime)
{
	if (bDestroy)
	{
		Destroy();
	}

	if (bHit && !bDestroy)
	{
		MeshComponent->SetVisibility(false);
		SetActorEnableCollision(false);
		ExplosionFX->Activate();
		ExplosionSound->Activate();
		ParticleSystem->Deactivate();
		fDestroyTimer -= DeltaTime;

		if (fDestroyTimer <= 0.0f)
		{
			bDestroy = true;
		}

		if (!bSpawnedPickup)
		{
			bSpawnedPickup = true;
			FActorSpawnParameters Params = {};
			GetWorld()->SpawnActor(Pickup, &CurrentLocation, &CurrentRotation, Params);
		}
	}
}

void AEnemy::ProcessTranslation(float DeltaTime)
{
	TotalTime += DeltaTime;

	CurrentLocation = GetActorLocation();
	CurrentRotation = GetActorRotation();

	CurrentLocation.Y += FMath::Sin((TotalTime + RandomStart) * 5.0f);

	SetActorLocation(CurrentLocation - (CurrentVelocity * DeltaTime));
}

void AEnemy::ProcessFiring(float DeltaTime)
{
	FiringCoolTime -= DeltaTime;
	if (FiringCoolTime <= 0.0f && !bHit)
	{
		FiringCoolTime = WeaponFireRate;
		FActorSpawnParameters Params = {};
		Params.Owner = this;

		GetWorld()->SpawnActor(EnemyProjectile, &CurrentLocation, &CurrentRotation, Params);
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

