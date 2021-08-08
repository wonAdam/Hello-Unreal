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

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABall> BallClass;

};
