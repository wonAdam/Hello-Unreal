// Fill out your copyright notice in the Description page of Project Settings.


#include "Bumper.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Ball.h"

// Sets default values
ABumper::ABumper()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	BumperBaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BumperBaseMesh"));
	BumperMechanismMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BumperMechanismMesh"));
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));

	RootComponent = RootComp;
	BumperBaseMeshComp->SetupAttachment(RootComp);
	BumperBaseMeshComp->SetRelativeLocation(FVector::ZeroVector);
	BumperMechanismMeshComp->SetupAttachment(RootComp);
	BumperMechanismMeshComp->SetRelativeLocation(FVector::ZeroVector);
	CapsuleCollision->SetupAttachment(RootComp);
	CapsuleCollision->SetRelativeLocation(FVector::ZeroVector);

}

// Called when the game starts or when spawned
void ABumper::BeginPlay()
{
	Super::BeginPlay();
	
	//CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::BeginOverlap);
}

// Called every frame
void ABumper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABumper::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (ABall* Ball = Cast<ABall>(OtherActor))
	{
		Bump(Ball);
	}
}

void ABumper::Bump(ABall* Ball)
{
	FVector BallLocation = Ball->GetActorLocation();
	FVector MyLocation = GetActorLocation();
	FVector UnitDirection = (BallLocation - MyLocation).GetSafeNormal();

	Ball->MeshComp->AddImpulse(UnitDirection * 1500.0f, NAME_None, true);
}

