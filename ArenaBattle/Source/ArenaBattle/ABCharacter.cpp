// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"

// Sets default values
AABCharacter::AABCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
}

void AABCharacter::SetControlMode(EControlMode Mode)
{
	ControlMode = Mode;
	switch (Mode)
	{
	case EControlMode::GTA:
	{
		GetController()->SetControlRotation(SpringArm->GetRelativeRotation());
		SpringArm->TargetArmLength = 450.0f;
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;

		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	}

	case EControlMode::DIABLO:
	{
		GetController()->SetControlRotation(GetActorRotation());
		SpringArm->TargetArmLength = 800.0f;
		SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;

		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	}
	}
}


// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetControlMode(ControlMode);
}

// Called every frame
void AABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABCharacter::OnViewChange_Implementation()
{
	switch (ControlMode)
	{
	case EControlMode::GTA:
	{
		SetControlMode(EControlMode::DIABLO);
		break;
	}

	case EControlMode::DIABLO:
	{
		SetControlMode(EControlMode::GTA);
		break;
	}
	}
}


void AABCharacter::OnUpDown_Implementation(float NewAxisValue)
{
	switch (ControlMode)
	{
	case EControlMode::GTA:
	{
		AddMovementInput(
			FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), 
			NewAxisValue * 100.0f
		);
		break;
	}
	case EControlMode::DIABLO:
	{
		AddMovementInput(
			FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::X),
			NewAxisValue * 100.0f
		);
		if (NewAxisValue != 0.0f)
		{
			FVector Direction = GetCharacterMovement()->Velocity;
			GetController()->SetControlRotation(
				Direction.Rotation());
		}
		break;
	}
	}
}

void AABCharacter::OnLeftRight_Implementation(float NewAxisValue)
{
	switch (ControlMode)
	{
	case EControlMode::GTA:
	{
		AddMovementInput(
			FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), 
			NewAxisValue * 100.0f
		);
		break;
	}
	case EControlMode::DIABLO:
	{
		AddMovementInput(
			FRotationMatrix(Camera->GetComponentRotation()).GetUnitAxis(EAxis::Y),
			NewAxisValue * 100.0f
		);
		if (NewAxisValue != 0.0f)
		{
			FVector Direction = GetCharacterMovement()->Velocity;
			GetController()->SetControlRotation(
				Direction.Rotation());
		}
		break;
	}
	}
}

void AABCharacter::OnLookUp_Implementation(float NewAxisValue)
{
	switch (ControlMode)
	{
	case EControlMode::GTA:
	{
		AddControllerPitchInput(NewAxisValue);
		break;
	}
	}
}

void AABCharacter::OnTurn_Implementation(float NewAxisValue)
{
	switch (ControlMode)
	{
	case EControlMode::GTA:
	{
		AddControllerYawInput(NewAxisValue);
		break;
	}
	}
}

// Called to bind functionality to input
void AABCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABCharacter::OnUpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABCharacter::OnLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AABCharacter::OnLookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AABCharacter::OnTurn);
	PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed , this, &AABCharacter::OnViewChange);
}