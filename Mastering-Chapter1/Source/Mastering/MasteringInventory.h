// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MasteringInventory.generated.h"

class AMasteringWeapon;
class AMasteringCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MASTERING_API UMasteringInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMasteringInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMasteringWeapon> DefaultWeapon;

	void SelectBestWeapon(AMasteringCharacter* Player);

	void SelectWeapon(AMasteringCharacter* Player, TSubclassOf<AMasteringWeapon> Weapon);

	void AddWeapon(TSubclassOf<AMasteringWeapon> Weapon);

	void AddDefaultWeapon();

	FORCEINLINE TSubclassOf<AMasteringWeapon> GetCurrentWeapon() const
	{
		return CurrentWeapon;
	}

protected:
	TArray<TSubclassOf<AMasteringWeapon>> WeaponsArray;

	TSubclassOf<AMasteringWeapon> CurrentWeapon;


		
};
