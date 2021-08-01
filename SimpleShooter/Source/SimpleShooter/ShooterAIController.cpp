// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!AIBehavior) return;

	RunBehaviorTree(AIBehavior);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UBlackboardComponent* BlackBoard = GetBlackboardComponent();
	Blackboard->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	Blackboard->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	AShooterCharacter* Shooter = Cast<AShooterCharacter>(GetPawn());
	Blackboard->SetValueAsVector(TEXT("StartPatrol"), Shooter->PatrolStart->GetActorLocation());
	Blackboard->SetValueAsVector(TEXT("EndPatrol"), Shooter->PatrolEnd->GetActorLocation());


	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//SetFocus(PlayerPawn);
	//MoveToActor(PlayerPawn, 10);
	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//SetFocus(PlayerPawn);

}


void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AShooterCharacter* Shooter = Cast<AShooterCharacter>(GetPawn());
	if (!Shooter) return;
	UBlackboardComponent* BlackBoard = GetBlackboardComponent();


	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (LineOfSightTo(PlayerPawn) && !Shooter->IsDead())
	{
		Blackboard->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		Blackboard->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	}
	else if(!LineOfSightTo(PlayerPawn))
	{
		Blackboard->ClearValue(TEXT("PlayerLocation"));
	}
}