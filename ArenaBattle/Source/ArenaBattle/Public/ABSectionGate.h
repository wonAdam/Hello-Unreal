// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Components/StaticMeshComponent.h"
#include "ABSectionGate.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABSectionGate : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UABSectionGate();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaSeconds, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void Open(bool bImmediate = false);

	void Close(bool bImmediate = false);

private:
	UPROPERTY(VisibleAnywhere)
	float Speed;

	UPROPERTY(VisibleAnywhere)
	FRotator InitialRotation;

	UPROPERTY(VisibleAnywhere)
	FRotator TargetRotation;

	UPROPERTY(VisibleAnywhere)
	FRotator OpenRotation;
};
