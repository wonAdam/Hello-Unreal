// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS(BlueprintType)
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// overriding AActor::TakeDamage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


private:
	bool bIsCrunched;

	bool bIsDead;

public:
	UFUNCTION(BlueprintPure)
	bool IsDead() const { return bIsDead; }

	UFUNCTION(BlueprintPure)
	bool IsCrunched() const { return bIsCrunched; }

private:
	UPROPERTY(EditAnywhere)
	float RotationRate = 80.0f;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	bool bIsRunning = false;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY(VisibleAnywhere)
	AGun* Gun;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void OnShiftKeyPressed();
	void OnShiftKeyReleased();
	void OnShootKeyPressed();
	void OnCtrlKeyPressed();
	void OnCtrlKeyReleased();
};
