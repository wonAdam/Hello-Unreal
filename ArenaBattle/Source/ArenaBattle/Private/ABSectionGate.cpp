// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSectionGate.h"

UABSectionGate::UABSectionGate()
{
	PrimaryComponentTick.bCanEverTick = true;
	Speed = 20.0f;
}

void UABSectionGate::BeginPlay()
{
	Super::BeginPlay();

	InitialRotation = GetComponentRotation();
	TargetRotation = InitialRotation;
	OpenRotation = InitialRotation + FRotator(0.0f, 90.0f, 0.0f);
}

void UABSectionGate::TickComponent(float DeltaSeconds, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaSeconds, TickType, ThisTickFunction);

	FRotator CurrentRotation = GetComponentRotation();
	if ((TargetRotation - CurrentRotation).IsNearlyZero())
		return;

	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, Speed);
	SetRelativeRotation(NewRotation);
}

void UABSectionGate::Open(bool bImmediate)
{
	TargetRotation = OpenRotation;

	if (bImmediate)
	{
		SetRelativeRotation(TargetRotation);
	}
}

void UABSectionGate::Close(bool bImmediate)
{
	TargetRotation = InitialRotation;

	if (bImmediate)
	{
		SetRelativeRotation(TargetRotation);
	}
}