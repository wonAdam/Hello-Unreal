// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "ABPawn.generated.h"

UCLASS()
class ARENABATTLE_API AABPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AABPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnUpDown(float NewAxisValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnLeftRight(float NewAxisValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	virtual void PossessedBy(AController* NewControlller) override;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, Category = Components)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UFloatingPawnMovement* Movement;

	UPROPERTY(VisibleAnywhere, Category = Components)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UCameraComponent* Camera;
};
