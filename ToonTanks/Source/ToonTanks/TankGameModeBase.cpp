// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Get References and game win/lose conditions
	// Call HandleGameStart() to initialize the start countdown, turret activation, pawn etc
	HandleGameStart();
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();

}

void ATankGameModeBase::HandleGameStart()
{
	// Initialize the start countdown, turrent activation, pawn check etc.
	TargetTurrets = GetTargetTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	// Call blueprint version GameStart()
	GameStart();

	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnableState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
			&APlayerControllerBase::SetPlayerEnableState, true);

		GetWorld()->GetTimerManager().SetTimer(
			PlayerEnableHandle, 
			PlayerEnableDelegate,
			(float)StartDelay, 
			false);
	}
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	// See if the player has destroyed all the turrets, show win result.
	// else if turret destroyed player, show lose result.
	// Call blueprint version GameOver(bool).
	GameOver(PlayerWon);
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	// Check what type of Actor died. If Turret, tally. If Player -> go to lose condition.
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnableState(false);
		}
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		if (--TargetTurrets <= 0)
		{
			HandleGameOver(true);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("A Pawn Died"));
}
