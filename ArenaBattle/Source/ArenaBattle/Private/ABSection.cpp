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
	Mesh->SetupAttachment(RootComponent);

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

void AABSection::SetState(ESectionState NewState)
{
	switch (NewState)
	{
	case ESectionState::READY:
	{
		OperateGates(true);
		break;
	}
	case ESectionState::BATTLE:
	{
		OperateGates(false);
		break;
	}
	case ESectionState::COMPLETE:
	{
		OperateGates(true);
		break;
	}


	}
}

void AABSection::SetGatesLocationToSockets()
{
	//static FName SocketNames[] = { TEXT("Gate0"), TEXT("Gate1"), TEXT("Gate2"), TEXT("Gate3") };
	//Gate00->SetupAttachment(Mesh, SocketNames[0]);
	//Gate00->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
	//Gate01->SetupAttachment(Mesh, SocketNames[1]);
	//Gate01->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
	//Gate02->SetupAttachment(Mesh, SocketNames[2]);
	//Gate02->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
	//Gate03->SetupAttachment(Mesh, SocketNames[3]);
	//Gate03->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
}

void AABSection::OperateGates(bool bOpen)
{
	/*GateMesh00->SetRelativeRotation(bOpen ? FRotator(0.0f, -90.0f, 0.0f) : FRotator::Zer)*/
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

