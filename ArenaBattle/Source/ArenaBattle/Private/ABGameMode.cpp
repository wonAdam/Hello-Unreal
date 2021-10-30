// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameMode.h"
#include "ABPawn.h"
#include "ABPlayerController.h"

AABGameMode::AABGameMode()
{
	//DefaultPawnClass = AABPawn::StaticClass();
	PlayerControllerClass = AABPlayerController::StaticClass();

	// Blueprint'/Game/ThirdPersonBP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter'
	// Blueprint'/Game/Blueprints/BP_ABPawn.BP_ABPawn'
	// Blueprint'/Game/Blueprints/BP_ABCharacter.BP_ABCharacter'
	static ConstructorHelpers::FClassFinder<APawn> BP_ABPAWN_C(TEXT("/Game/Blueprints/BP_ABCharacter.BP_ABCharacter_C"));
	if (BP_ABPAWN_C.Succeeded())
	{
		DefaultPawnClass = BP_ABPAWN_C.Class;
	}
}

void AABGameMode::PostLogin(APlayerController* NewPlayer)
{
	ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	ABLOG(Warning, TEXT("PostLogin End"));
}
