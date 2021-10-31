// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSection.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "ABSectionGate.h"

// Sets default values
AABSection::AABSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Gate00 = CreateDefaultSubobject<UABSectionGate>(TEXT("Gate 0"));
	Gate00->SetupAttachment(RootComponent);
	Gate01 = CreateDefaultSubobject<UABSectionGate>(TEXT("Gate 1"));
	Gate01->SetupAttachment(RootComponent);
	Gate02 = CreateDefaultSubobject<UABSectionGate>(TEXT("Gate 2"));
	Gate02->SetupAttachment(RootComponent);
	Gate03 = CreateDefaultSubobject<UABSectionGate>(TEXT("Gate 3"));
	Gate03->SetupAttachment(RootComponent);

	CenterBoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Center BoxTrigger"));
	CenterBoxTrigger->SetupAttachment(RootComponent);
	GateBoxTrigger00 = CreateDefaultSubobject<UBoxComponent>(TEXT("Gate00 BoxTrigger"));
	GateBoxTrigger00->SetupAttachment(RootComponent);
	GateBoxTrigger01 = CreateDefaultSubobject<UBoxComponent>(TEXT("Gate01 BoxTrigger"));
	GateBoxTrigger01->SetupAttachment(RootComponent);
	GateBoxTrigger02 = CreateDefaultSubobject<UBoxComponent>(TEXT("Gate02 BoxTrigger"));
	GateBoxTrigger02->SetupAttachment(RootComponent);
	GateBoxTrigger03 = CreateDefaultSubobject<UBoxComponent>(TEXT("Gate03 BoxTrigger"));
	GateBoxTrigger03->SetupAttachment(RootComponent);

	bNoBattle = false;
}

void AABSection::SetState(ESectionState NewState, bool bImmediate)
{
	switch (NewState)
	{
	case ESectionState::READY:
	{
		OperateGates(true, bImmediate);
		break;
	}
	case ESectionState::BATTLE:
	{
		OperateGates(false, bImmediate);
		break;
	}
	case ESectionState::COMPLETE:
	{
		OperateGates(true, bImmediate);
		break;
	}
	}
}

void AABSection::OperateGates(bool bOpen, bool bImmediate)
{
	if (bOpen)
	{
		Gate00->Open(bImmediate);
		Gate01->Open(bImmediate);
		Gate02->Open(bImmediate);
		Gate03->Open(bImmediate);
	}
	else
	{
		Gate00->Close(bImmediate);
		Gate01->Close(bImmediate);
		Gate02->Close(bImmediate);
		Gate03->Close(bImmediate);
	}
}

void AABSection::OnCenterTriggerBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent*
	OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	FHitResult& SweepResult)
{

}

void AABSection::OnGateTriggerBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent*
	OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	FHitResult& SweepResult)
{

}

// Called when the game starts or when spawned
void AABSection::BeginPlay()
{
	Super::BeginPlay();
	
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}

// Called every frame
void AABSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

