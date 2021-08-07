// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flipper.generated.h"

UENUM(BlueprintType)
enum class EFlipperType : uint8
{
	Right,
	Left
};

UCLASS()
class PINBALL_API AFlipper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlipper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void Flip();

	UFUNCTION(BlueprintCallable)
	void Flop();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFlipperType Type;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FRotator StartRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FRotator EndRotation;
};
