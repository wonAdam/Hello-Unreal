// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "Gun.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

	Health = MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ThisClass::LookUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ThisClass::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &ThisClass::LookRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ThisClass::Jump);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &ThisClass::OnShiftKeyPressed);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &ThisClass::OnShiftKeyReleased);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &ThisClass::OnShootKeyPressed);
	PlayerInputComponent->BindAction(TEXT("Crunch"), EInputEvent::IE_Pressed, this, &ThisClass::OnCtrlKeyPressed);
	PlayerInputComponent->BindAction(TEXT("Crunch"), EInputEvent::IE_Released, this, &ThisClass::OnCtrlKeyReleased);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsDead) return 0.0f;

	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageApplied = FMath::Min(Health, DamageApplied);

	Health -= DamageApplied;

	if (Health == 0.0f)
	{
		bIsDead = true;
	}

	return DamageApplied;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	if(!bIsRunning || bIsCrunched)
		AxisValue /= 3;

	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	if (!bIsRunning || bIsCrunched)
		AxisValue /= 3;

	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::OnShiftKeyPressed()
{
	bIsRunning = true;
}

void AShooterCharacter::OnShiftKeyReleased()
{
	bIsRunning = false;
}

void AShooterCharacter::OnCtrlKeyPressed()
{
	bIsCrunched = true;
}

void AShooterCharacter::OnCtrlKeyReleased()
{
	bIsCrunched = false;
}

void AShooterCharacter::OnShootKeyPressed()
{
	if (Gun)
	{
		Gun->PullTrigger();
	}
}


