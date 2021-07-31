// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	RootComponent = Root;
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController) return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(OUT Location, OUT Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);
	//DrawDebugPoint(GetWorld(), Location, 20, FColor::Yellow, true);

	FHitResult HitResult;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECollisionChannel::ECC_GameTraceChannel1);

	if (HitResult.bBlockingHit)
	{
		DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
		DrawDebugLine(GetWorld(), Location, HitResult.Location, FColor::Red, true, 1, 0, 2);
	}

	if (bSuccess)
	{
		DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
		DrawDebugLine(GetWorld(), Location, HitResult.Location, FColor::Red, true, 1, 0, 2);
	}

}

