// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "SS_Player.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));

	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

void APickup::OnBeginOverlap(AActor* PickupActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Bounds"))
	{
		// Off the Bounds
		Destroy();
	}

	if (OtherActor->ActorHasTag("Player"))
	{
		// Picked Up
		ASS_Player* PlayerActor = Cast<ASS_Player>(OtherActor);
		PlayerActor->CollectPickup();
		SetActorEnableCollision(false);
		Destroy();
	}
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation.X -= DeltaTime * 100.0f;
	NewLocation.Z = 0.0f;
	SetActorLocation(NewLocation);
}


