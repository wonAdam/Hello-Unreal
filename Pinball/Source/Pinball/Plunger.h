// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plunger.generated.h"

//struct FTimeline;

UCLASS()
class PINBALL_API APlunger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlunger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UFUNCTION(BlueprintImplementableEvent)
	void ChargePlunger();

	UFUNCTION(BlueprintImplementableEvent)
	void StopCharge();

	UFUNCTION(BlueprintImplementableEvent)
	FVector GetBallSpawningLocation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComp;

//	FTimeline ChargeTimeline;


};
