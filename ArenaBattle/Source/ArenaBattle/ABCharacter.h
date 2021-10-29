// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Character.h"
#include "ABCharacter.generated.h"

class UABAnimInstance;
class UABCharacterStatComponent;
class UWidgetComponent;

UENUM()
enum class EControlMode : uint8
{
	GTA,
	DIABLO,
	NPC,
};

UCLASS()
class ARENABATTLE_API AABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacter();

	virtual float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser) override;

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
	void OnAttackHitCheck();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void PossessedBy(AController* NewController) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetWeapon(class AABWeapon* NewWeapon);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanSetWeapon();

	UPROPERTY(VisibleAnywhere, Category = Components)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	UABCharacterStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere, Category = UI)
	UWidgetComponent* HPBarWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
	class AABWeapon* CurrentWeapon;

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

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess))
	float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess))
	float AttackRadius;
};
