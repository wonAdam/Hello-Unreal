// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ABCharacter.h"
#include "ABCharacterStatComponent.h"

const FName AABAIController::SpawnPosKey(TEXT("SpawnPos"));
const FName AABAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AABAIController::TargetKey(TEXT("Target"));

AABAIController::AABAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void AABAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AABAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ABLOG(Warning, TEXT("OnPossess"));

	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(SpawnPosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			ABLOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
		ABLOG(Warning, TEXT("SpawnPosKey: %s"), *Blackboard->GetValueAsVector(SpawnPosKey).ToString());
	}

	auto ABCharacter = Cast<AABCharacter>(GetPawn());
	if (ABCharacter != nullptr)
	{
		ABCharacter->CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
			UnPossess();
			});
	}
}
