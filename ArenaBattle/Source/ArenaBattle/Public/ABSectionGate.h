// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	void Open();

	void Close();
};
