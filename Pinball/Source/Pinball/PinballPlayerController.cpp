// Fill out your copyright notice in the Description page of Project Settings.


#include "PinballPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Flipper.h"
#include "Plunger.h"

// Called when the game starts or when spawned
void APinballPlayerController::BeginPlay()
{
	Super::BeginPlay();

	DetectFlippers();

	DetectPlunger();
}

void APinballPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftFlipper", IE_Pressed, this, &ThisClass::OnPressedLeftCtrl);
	InputComponent->BindAction("LeftFlipper", IE_Released, this, &ThisClass::OnReleasedLeftCtrl);
	InputComponent->BindAction("RightFlipper", IE_Pressed, this, &ThisClass::OnPressedRightCtrl);
	InputComponent->BindAction("RightFlipper", IE_Released, this, &ThisClass::OnReleasedRightCtrl);
	InputComponent->BindAction("Plunger", IE_Pressed, this, &ThisClass::OnPressedPlunger);
	InputComponent->BindAction("Plunger", IE_Released, this, &ThisClass::OnReleasedPlunger);
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

void APinballPlayerController::OnPressedPlunger()
{
	Plunger->ChargePlunger();
}

void APinballPlayerController::OnReleasedPlunger()
{
	Plunger->StopCharge();
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

void APinballPlayerController::DetectPlunger()
{
	Plunger = Cast<APlunger>(UGameplayStatics::GetActorOfClass(GetWorld(), APlunger::StaticClass()));
}
