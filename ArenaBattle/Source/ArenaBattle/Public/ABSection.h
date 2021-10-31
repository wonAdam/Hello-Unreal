// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Actor.h"
#include "ABSection.generated.h"

class UABSectionGate;

UENUM()
enum class ESectionState : uint8
{
	READY = 0,
	BATTLE,
	COMPLETE
};

UCLASS()
class ARENABATTLE_API AABSection : public AActor
{
	GENERATED_BODY()

private:
	void SetState(ESectionState NewState, bool bImmediate = false);

	UPROPERTY(VisibleAnywhere)
	ESectionState CurrentState = ESectionState::READY;

	void OperateGates(bool bOpen = true, bool bImmediate = false);

	UFUNCTION()
	void OnCenterTriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* 
		OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		FHitResult& SweepResult);

	UFUNCTION()
		void OnGateTriggerBeginOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent*
			OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			FHitResult& SweepResult);

public:	
	// Sets default values for this actor's properties
	AABSection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UABSectionGate* Gate00;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UABSectionGate* Gate01;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UABSectionGate* Gate02;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UABSectionGate* Gate03;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UBoxComponent* CenterBoxTrigger;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UBoxComponent* GateBoxTrigger00;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UBoxComponent* GateBoxTrigger01;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UBoxComponent* GateBoxTrigger02;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UBoxComponent* GateBoxTrigger03;
	
	UPROPERTY(EditAnywhere, Category = State, Meta = (AllowPrivateAccess = true))
	bool bNoBattle;
};
