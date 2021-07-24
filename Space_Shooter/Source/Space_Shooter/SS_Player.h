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

	UPROPERTY(EditAnywhere)
	float Field_Width;

	UPROPERTY(EditAnywhere)
	float Field_Height;

	UPROPERTY(VisibleAnywhere)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere)
	float MaxArmor;

	UPROPERTY(VisibleAnywhere)
	float CurrentArmor;

public:
	void MoveRight(float AxisValue);

	void MoveUp(float AxisValue);

	void StartFiring();

	void StopFiring();

	void FireWeapon();

	UPROPERTY(EditAnywhere)
	float MaxVelocity;

	UPROPERTY(VisibleAnywhere)
	bool bIsFiring;

	UPROPERTY(VisibleAnywhere)
	float WeaponFireRate;

	UPROPERTY(VisibleAnywhere)
	float TimeSinceLastShot;

	UPROPERTY(VisibleAnywhere)
	bool bHit;

	UPROPERTY(VisibleAnywhere)
	bool bDead;

	UPROPERTY(VisibleAnywhere)
	float Current_X_Velocity;

	UPROPERTY(VisibleAnywhere)
	float Current_Y_Velocity;

	UPROPERTY(VisibleAnywhere)
	float PlayerScore;

	UPROPERTY(VisibleAnywhere)
	FVector CurrentLocation;

	UPROPERTY(VisibleAnywhere)
	FRotator CurrentRotation;

	UPROPERTY(VisibleAnywhere)
	FRotator InitialRotation;

	UPROPERTY(VisibleAnywhere)
	FVector NewLocation;

	UFUNCTION()
	void OnBeginOverlap(AActor* PlayerActor, AActor* OtherActor);

	//UPROPERTY(EditAnywhere)
	//	TSubclassOf<AProjectile> WeaponProjectile_BP;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ProcessRotation(float DeltaTime);

	void ProcessTranslation(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
