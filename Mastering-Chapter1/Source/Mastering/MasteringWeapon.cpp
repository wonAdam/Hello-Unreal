// Fill out your copyright notice in the Description page of Project Settings.


#include "MasteringWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "MasteringProjectile.h"

// Sets default values
AMasteringWeapon::AMasteringWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh Comp"));
	WeaponMesh->SetOnlyOwnerSee(true);
	WeaponMesh->bCastDynamicShadow = false;
	WeaponMesh->CastShadow = false;
	WeaponMesh->SetupAttachment(RootComponent);

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLocation->SetupAttachment(WeaponMesh);
}

// Called when the game starts or when spawned
void AMasteringWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasteringWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMasteringWeapon::Fire(FRotator ControlRotation, UAnimInstance* AnimInst)
{
	if (ProjectileClass != nullptr)
	{
		if (GetWorld() != nullptr)
		{
			const FVector SpawnLocation = ((MuzzleLocation != nullptr) ?
				MuzzleLocation->GetComponentLocation() : GetActorLocation() + ControlRotation.RotateVector(GunOffset));
		
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			GetWorld()->SpawnActor<AMasteringProjectile>(ProjectileClass, SpawnLocation, ControlRotation, ActorSpawnParams);
		}
	}

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (FireAnimation != nullptr)
	{
		if (AnimInst != nullptr)
		{
			AnimInst->Montage_Play(FireAnimation);
		}
	}
}
