// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SS_Player.generated.h"	

UCLASS()
class SPACE_SHOOTER_API ASS_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASS_Player();

public:
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ExplosionFX;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ShipMesh;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
	UAudioComponent* DeathExplosionSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
