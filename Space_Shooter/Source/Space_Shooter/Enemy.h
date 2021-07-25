// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "Enemy.generated.h"

UCLASS()
class SPACE_SHOOTER_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleCollision;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ExplosionFX;

	UPROPERTY(EditAnywhere)
	UAudioComponent* ExplosionSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> EnemyProjectile;

	UWorld* ThisWorld;

	UPROPERTY(EditAnywhere)
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere)
	float WeaponFireRate;

	float TotalTime;
	float FiringCoolTime;
	float RandomStart;

	bool bHit;
	bool bDestroy;

	float fDestroyTimer;
	float fBurstDelay;

	FVector CurrentLocation;
	FRotator CurrentRotation;

	UFUNCTION()
	void OnBeginOverlap(AActor* EnemyActor, AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ProcessDestruction(float DeltaTime);

	void ProcessTranslation(float DeltaTime);

	void ProcessFiring(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
