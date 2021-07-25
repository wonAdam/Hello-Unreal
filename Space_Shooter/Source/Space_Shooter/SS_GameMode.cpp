// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_GameMode.h"

ASS_GameMode::ASS_GameMode()
{
	SpawnTimer = 0.0f;

	MusicTrack = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicTrack"));
	MusicTrack->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ThisWorld = GetWorld();
}


void ASS_GameMode::BeginPlay()
{
	Super::BeginPlay();

	MusicTrack->Play();

	bPlayerDead = false;
}

void ASS_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	SpawnTimer = FMath::RandRange(0, 1000);

	if (Enemy)
	{
		if (SpawnTimer > 999)
		{
			FVector EnemySpawnLoc(1000.0f, FMath::RandRange(-500.0f, 500.0f), 0.0f);
			FRotator EnemySpawnRot(0.0f, 0.0f, 0.0f);

			AActor* NewEnemy = 
				GetWorld()->SpawnActor(
					Enemy, 
					&EnemySpawnLoc, 
					&EnemySpawnRot, 
					AsteroidSpawnParameters
				);
		}
	}

	if (HazardTemplate)
	{
		if (SpawnTimer > 995)
		{
			FVector AsteroidSpawnLoc(1000.0f, FMath::RandRange(-500.0f, 500.0f), 0.0f);
			FRotator AsteroidSpawnRot(0.0f, 0.0f, 0.0f);
			
			AActor* NewHazard =
				GetWorld()->SpawnActor(
					HazardTemplate,
					&AsteroidSpawnLoc,
					&AsteroidSpawnRot,
					AsteroidSpawnParameters
				);
		}
	}
}

void ASS_GameMode::RestartLevel(FName LevelName)
{

}