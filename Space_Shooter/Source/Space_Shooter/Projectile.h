// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.generated.h"

UCLASS()
class SPACE_SHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleCollision;

	UPROPERTY(EditAnywhere)
	float ProjectileSpeed;

	UFUNCTION()
	void OnBeginOverlap(AActor* ProjectileActor, AActor* OtherActor);

	UPROPERTY(VisibleAnywhere)
	FVector CurrentLocation;

	UPROPERTY(VisibleAnywhere)
	bool bHit;

	UPROPERTY(VisibleAnywhere)
	bool bDestory;

private:
	void ProcessTranslation(float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
