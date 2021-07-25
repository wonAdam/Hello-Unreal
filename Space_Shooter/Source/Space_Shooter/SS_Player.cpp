// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Player.h"

// Sets default values
ASS_Player::ASS_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	ExplosionFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionFX"));
	DeathExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("DeathExplosionSound"));

	ShipMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ParticleSystem->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	DeathExplosionSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	MaxVelocity = 250.0f;
	Current_X_Velocity = 0.0f;
	Current_Y_Velocity = 0.0f;

	bIsFiring = false;
	WeaponFireRate = 0.25f;
	FiringCoolTime = 0.0f;
	PlayerScore = 0.0f;

	WeaponProjectile_BP = AProjectile::StaticClass();
}

void ASS_Player::MoveRight(float AxisValue)
{
	Current_X_Velocity = MaxVelocity * AxisValue;

	if (AxisValue < 0.0f)
	{
		ParticleSystem->Deactivate();
	}
	else
	{
		ParticleSystem->Activate();
	}
}

void ASS_Player::MoveUp(float AxisValue)
{
	Current_Y_Velocity = -MaxVelocity * AxisValue;
}

void ASS_Player::StartFiring()
{
	bIsFiring = true;
}

void ASS_Player::StopFiring()
{
	bIsFiring = false;
}

void ASS_Player::FireWeapon()
{
	FActorSpawnParameters Params = {};
	Params.Owner = this;
	
	GetWorld()->SpawnActor(WeaponProjectile_BP, &CurrentLocation, &CurrentRotation, Params);
}

void ASS_Player::OnBeginOverlap(AActor* PlayerActor, AActor* OtherActor)
{



}

// Called when the game starts or when spawned
void ASS_Player::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentLocation = GetActorLocation();
	InitialRotation = CurrentRotation = GetActorRotation();

	bHit = false;
	bDead = false;

	ExplosionFX->Deactivate();
	DeathExplosionSound->Deactivate();

	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
	MaxArmor = 100.0f;
	CurrentArmor = MaxArmor;

	OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

// Called every frame
void ASS_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProcessTranslation(DeltaTime);

	ProcessRotation(DeltaTime);

	ProcessFiring(DeltaTime);
}

void ASS_Player::ProcessRotation(float DeltaTime)
{
	float Delta = DeltaTime * RotatingSpeed;
	if (Current_Y_Velocity > 0.1f)
	{
		CurrentRotation.Pitch -= Delta;
		CurrentRotation.Pitch = FMath::Clamp(CurrentRotation.Pitch, InitialRotation.Pitch - 45.0f, InitialRotation.Pitch + 45.0f);
	}

	else if (Current_Y_Velocity < -0.1f)
	{
		CurrentRotation.Pitch += Delta;
		CurrentRotation.Pitch = FMath::Clamp(CurrentRotation.Pitch, InitialRotation.Pitch - 45.0f, InitialRotation.Pitch + 45.0f);
	}

	else
	{
		float PitchDiff = InitialRotation.Pitch - CurrentRotation.Pitch;
		CurrentRotation.Pitch += FMath::Sign(PitchDiff) * Delta;
		if (FMath::Abs(PitchDiff) < Delta)
		{
			CurrentRotation = InitialRotation;
		}
	}

	SetActorRotation(CurrentRotation);
}

void ASS_Player::ProcessTranslation(float DeltaTime)
{
	if (Current_X_Velocity != 0.0f || Current_Y_Velocity != 0.0f)
	{
		NewLocation = FVector(
			FMath::Clamp(CurrentLocation.X + (Current_X_Velocity * DeltaTime), -Field_Width / 2.0f, Field_Width / 2.0f),
			FMath::Clamp(CurrentLocation.Y + (Current_Y_Velocity * DeltaTime), -Field_Height / 2.0f, Field_Height / 2.0f),
			0.0f
		);

		SetActorLocation(NewLocation);

		CurrentLocation = NewLocation;
	}
}


void ASS_Player::ProcessFiring(float DeltaTime)
{
	if (FiringCoolTime > 0.0f)
	{
		FiringCoolTime = FMath::Max(FiringCoolTime - DeltaTime, 0.0f);
	}

	if (bIsFiring && FiringCoolTime <= 0.0f)
	{
		FireWeapon();
		FiringCoolTime = WeaponFireRate;
	}
}

void ASS_Player::CollectPickup()
{
	if (CurrentHealth < MaxHealth)
	{
		CurrentHealth = FMath::Min(CurrentHealth + 30, MaxHealth);
	}
	else if (CurrentArmor < MaxArmor)
	{
		CurrentArmor = FMath::Min(CurrentArmor + 30, MaxArmor);
	}
}

void ASS_Player::GetDamage(float Amount)
{
	if (CurrentArmor > 0.0f)
	{
		CurrentArmor = FMath::Max(CurrentArmor - Amount, 0.0f);
	}
	else if (CurrentHealth > 0.0f)
	{
		CurrentHealth = FMath::Max(CurrentHealth - Amount, 0.0f);
	}
}

// Called to bind functionality to input
void ASS_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ThisClass::MoveRight);
	PlayerInputComponent->BindAxis(FName("MoveUp"), this, &ThisClass::MoveUp);
	PlayerInputComponent->BindAction(FName("Fire"), EInputEvent::IE_Pressed, this, &ThisClass::StartFiring);
	PlayerInputComponent->BindAction(FName("Fire"), EInputEvent::IE_Released, this, &ThisClass::StopFiring);
}

