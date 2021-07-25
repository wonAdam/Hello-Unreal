// Fill out your copyright notice in the Description page of Project Settings.


#include "Hazard.h"

// Sets default values
AHazard::AHazard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	AsteroidExplosionFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionFX"));
	AsteroidExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("DeathExplosionSound"));

	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	AsteroidExplosionFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	AsteroidExplosionSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Spawn_X_Velocity = -500.0f;
	Spawn_Y_Velocity = 0.0f;

	SelfDestructTimer = 1.0f;

	bHit = false;
}

void AHazard::SpawnChildren(int32 NumChildren)
{

}

void AHazard::SetHazardVelocity(FVector NewVelocity)
{

}

void AHazard::OnBeginOverlap(AActor* AsteroidActor, AActor* OtherActor)
{

}

// Called when the game starts or when spawned
void AHazard::BeginPlay()
{
	Super::BeginPlay();
	
	InitialRotation = 0.0f;
	Initial_X_Location = 1500.0f;
	Initial_Y_Location = FMath::RandRange(-500.0f, 500.0f);

	RandSize = FMath::RandRange(3.0f, 8.0f);
	SetActorScale3D(FVector(RandSize, RandSize, RandSize));

	AsteroidExplosionSound->Deactivate();
	AsteroidExplosionSound->bStopWhenOwnerDestroyed = false;
	AsteroidExplosionFX->Deactivate();

	OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

// Called every frame
void AHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	check(this != nullptr);

	InitialRotation += DeltaTime;

	Initial_X_Location += DeltaTime * Spawn_X_Velocity;
	Initial_Y_Location += DeltaTime * Spawn_Y_Velocity;

	SetActorRotation(FRotator(InitialRotation * 100.0f, InitialRotation * 50.0f, 0.0f));
	SetActorLocation(FVector(FVector(Initial_X_Location, Initial_Y_Location, 0.0f)));
}

