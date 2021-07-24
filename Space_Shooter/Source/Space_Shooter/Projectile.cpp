// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneComponent"));
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));

	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CapsuleCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileSpeed = 0.0f;
	bHit = false;
	bDestory = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentLocation = GetActorLocation();
	OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProcessTranslation(DeltaTime);
}

void AProjectile::ProcessTranslation(float DeltaTime)
{
	FVector NewLocation =
		FVector(
			CurrentLocation.X + (ProjectileSpeed * DeltaTime),
			CurrentLocation.Y,
			CurrentLocation.Z
		);

	SetActorLocation(NewLocation);

	CurrentLocation = NewLocation;
}

void AProjectile::OnBeginOverlap(AActor* ProjectileActor, AActor* OtherActor)
{
}

