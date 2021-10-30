// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "AIController.h"
#include "ABAIController.generated.h"

class UBehaviorTree;
class UBlackboardData;

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AABAIController();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	static const FName SpawnPosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BTAsset;

	UPROPERTY(EditAnywhere)
	UBlackboardData* BBAsset;

};
