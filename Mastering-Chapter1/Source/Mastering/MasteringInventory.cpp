// Fill out your copyright notice in the Description page of Project Settings.


#include "MasteringInventory.h"
#include "MasteringCharacter.h"

// Sets default values for this component's properties
UMasteringInventory::UMasteringInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMasteringInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMasteringInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMasteringInventory::SelectBestWeapon(AMasteringCharacter* Player)
{
	for (auto WeaponIt = WeaponsArray.CreateConstIterator(); WeaponIt; ++WeaponIt)
	{
		// TODO: 무기 선택을 위한 기준 추가
		{
			SelectWeapon(Player, *WeaponIt);
			break;
		}
	}
}

void UMasteringInventory::SelectWeapon(AMasteringCharacter* Player, TSubclassOf<AMasteringWeapon> Weapon)
{
	Player->EquipWeapon(Weapon);
}

void UMasteringInventory::AddWeapon(TSubclassOf<AMasteringWeapon> Weapon)
{
	WeaponsArray.AddUnique(Weapon);
}

void UMasteringInventory::AddDefaultWeapon()
{

}