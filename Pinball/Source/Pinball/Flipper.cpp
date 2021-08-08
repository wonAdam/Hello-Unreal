// Fill out your copyright notice in the Description page of Project Settings.


#include "Flipper.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

// Sets default values
AFlipper::AFlipper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	RootComponent = RootComp;
	MeshComp->SetupAttachment(RootComp);
}

// Called when the game starts or when spawned
void AFlipper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlipper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlipper::Flip()
{
	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.UUID = GetUniqueID();
	LatentActionInfo.ExecutionFunction = TEXT("");
	LatentActionInfo.Linkage = 0;

	UKismetSystemLibrary::MoveComponentTo(
		MeshComp,
		FVector::ZeroVector, 
		EndRotation, 
		false, 
		false,
		0.02f, 
		true,
		EMoveComponentAction::Move,
		LatentActionInfo
	);
}

void AFlipper::Flop()
{
	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.UUID = GetUniqueID();
	LatentActionInfo.ExecutionFunction = TEXT("");
	LatentActionInfo.Linkage = 0;

	UKismetSystemLibrary::MoveComponentTo(
		MeshComp,
		FVector::ZeroVector,
		StartRotation,
		false,
		false,
		0.15f,
		true,
		EMoveComponentAction::Move,
		LatentActionInfo
	);
}

