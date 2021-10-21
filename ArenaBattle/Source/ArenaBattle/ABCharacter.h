// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Character.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "ABCharacter.generated.h"

class UABAnimInstance;

UENUM()
enum class EControlMode : uint8
{
	GTA,
	DIABLO,
};

UCLASS()
class ARENABATTLE_API AABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ControlMode)
	EControlMode ControlMode;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnAttack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnJump();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnViewChange();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnUpDown(float NewAxisValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnLeftRight(float NewAxisValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnLookUp(float NewAxisValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnTurn(float NewAxisValue);

	UFUNCTION(BlueprintCallable)
	void SetControlMode(EControlMode Mode);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void OnNextAttackCheck();
	bool TryAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Components)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UCameraComponent* Camera;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess))
	bool IsAttacking;

	UPROPERTY()
	UABAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess))
	bool CanNextCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess))
	int32 CurrentCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess))
	int32 MaxCombo;
};
