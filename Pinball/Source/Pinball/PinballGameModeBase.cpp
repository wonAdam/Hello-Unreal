// Copyright Epic Games, Inc. All Rights Reserved.


#include "PinballGameModeBase.h"
#include "PinballPlayerController.h"

APinballGameModeBase::APinballGameModeBase()
{
	PlayerControllerClass = APinballPlayerController::StaticClass();
}