// Fill out your copyright notice in the Description page of Project Settings.


#include "PinballPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Flipper.h"

// Called when the game starts or when spawned
void APinballPlayerController::BeginPlay()
{
	Super::BeginPlay();

	DetectFlippers();
}

void APinballPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftFlipper", IE_Pressed, this, &ThisClass::OnPressedLeftCtrl);
	InputComponent->BindAction("LeftFlipper", IE_Released, this, &ThisClass::OnReleasedLeftCtrl);
	InputComponent->BindAction("RightFlipper", IE_Pressed, this, &ThisClass::OnPressedRightCtrl);
	InputComponent->BindAction("RightFlipper", IE_Released, this, &ThisClass::OnReleasedRightCtrl);
}

void APinballPlayerController::OnPressedLeftCtrl()
{
	for (auto* Flipper : LeftFlippers)
	{
		Flipper->Flip();
	}
}

void APinballPlayerController::OnReleasedLeftCtrl()
{
	for (auto* Flipper : LeftFlippers)
	{
		Flipper->Flop();
	}
}

void APinballPlayerController::OnPressedRightCtrl()
{
	for (auto* Flipper : RightFlippers)
	{
		Flipper->Flip();
	}
}

void APinballPlayerController::OnReleasedRightCtrl()
{
	for (auto* Flipper : RightFlippers)
	{
		Flipper->Flop();
	}
}

void APinballPlayerController::DetectFlippers()
{
	TArray<AActor*> Flippers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFlipper::StaticClass(), Flippers);

	for (auto* FlipperActor : Flippers)
	{
		AFlipper* Flipper = Cast<AFlipper>(FlipperActor);
		if (!Flipper)
			continue;

		if (Flipper->Type == EFlipperType::Right)
			RightFlippers.Add(Flipper);
		else
			LeftFlippers.Add(Flipper);
	}
}