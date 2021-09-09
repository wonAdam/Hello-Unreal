// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PinballGameModeBase.generated.h"

class ABall;

/**
 * 
 */
UCLASS()
class PINBALL_API APinballGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APinballGameModeBase();

public:
	UFUNCTION(BlueprintCallable)
	void SpawnBall();

	UFUNCTION()
	void OnBallDestroy(AActor* DestroyedActor);

	UFUNCTION(BlueprintCallable)
	int AddScore(int PointsToAdd);

	UFUNCTION(BlueprintCallable)
	void EndGame();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int BallsRemaining;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABall> BallClass;

};
