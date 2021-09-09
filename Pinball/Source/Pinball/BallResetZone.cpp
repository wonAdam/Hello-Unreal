// Fill out your copyright notice in the Description page of Project Settings.


#include "BallResetZone.h"
#include "Components/BoxComponent.h"
#include "Ball.h"

// Sets default values
ABallResetZone::ABallResetZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABallResetZone::BeginPlay()
{
	Super::BeginPlay();
	
	//BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::BeginOverlap);
}

// Called every frame
void ABallResetZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABallResetZone::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABall* Ball = Cast<ABall>(OtherActor))
	{
		GetWorld()->DestroyActor(Ball);
	}
}

