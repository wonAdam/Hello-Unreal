// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasteringWeapon.generated.h"

class AMasteringProjectile;
class USkeletalMeshComponent;
class USoundBase;
class UAnimMontage;

UCLASS()
class MASTERING_API AMasteringWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasteringWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire(FRotator ControlRotation, UAnimInstance* AnimInst);

private:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	FVector GunOffset;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	TSubclassOf<AMasteringProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	USceneComponent* MuzzleLocation;
};
