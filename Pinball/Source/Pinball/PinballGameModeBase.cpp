// Copyright Epic Games, Inc. All Rights Reserved.


#include "PinballGameModeBase.h"
#include "PinballPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Plunger.h"
#include "Ball.h"

APinballGameModeBase::APinballGameModeBase()
{
	PlayerControllerClass = APinballPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}

void APinballGameModeBase::SpawnBall()
{
	TArray<AActor*> Plungers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlunger::StaticClass(), Plungers);
	
	if (Plungers.Num() > 0)
	{
		APlunger* Plunger = Cast<APlunger>(Plungers[0]);
		FVector SpawnLocation = Plunger->GetBallSpawningLocation();
		
		FActorSpawnParameters Params;
		AActor* BallActor = GetWorld()->SpawnActor(BallClass, &SpawnLocation, &FRotator::ZeroRotator, Params);
		BallActor->OnDestroyed.AddDynamic(this, &ThisClass::OnBallDestroy);
	}
}

void APinballGameModeBase::OnBallDestroy(AActor* DestroyedActor)
{
	SpawnBall();
}
