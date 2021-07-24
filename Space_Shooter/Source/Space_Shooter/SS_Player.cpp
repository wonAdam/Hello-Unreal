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
	TimeSinceLastShot = 0.0f;
	PlayerScore = 0.0f;
}

void ASS_Player::MoveRight(float AxisValue)
{
	Current_X_Velocity = MaxVelocity * AxisValue;
}

void ASS_Player::MoveUp(float AxisValue)
{
	Current_Y_Velocity = -MaxVelocity * AxisValue;
}

void ASS_Player::StartFiring()
{
}

void ASS_Player::StopFiring()
{
}

void ASS_Player::FireWeapon()
{
}

void ASS_Player::OnBeginOverlap(AActor* PlayerActor, AActor* OtherActor)
{
}

// Called when the game starts or when spawned
void ASS_Player::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentLocation = GetActorLocation();
	CurrentRotation = GetActorRotation();

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

	if (Current_X_Velocity != 0.0f || Current_Y_Velocity != 0.0f)
	{
		NewLocation = FVector(
			CurrentLocation.X + (Current_X_Velocity * DeltaTime),
			CurrentLocation.Y + (Current_Y_Velocity * DeltaTime),
			0.f
		);

		SetActorLocation(NewLocation);

		CurrentLocation = NewLocation;
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

