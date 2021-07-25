// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Enemy.h"
#include "Hazard.h"
#include "SS_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACE_SHOOTER_API ASS_GameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemy> Enemy;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AHazard> HazardTemplate;

	UPROPERTY(EditAnywhere)
	UAudioComponent* MusicTrack;

public:
	ASS_GameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	float SpawnTimer;

	bool bPlayerDead;

	UFUNCTION()
	void RestartLevel(FName LevelName);

	bool bStart;

protected:
	FActorSpawnParameters AsteroidSpawnParameters;

	UWorld* ThisWorld;


	// Widgets
};
