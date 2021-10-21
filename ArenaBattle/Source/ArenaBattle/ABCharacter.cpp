// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"
#include "ABAnimInstance.h"

// Sets default values
AABCharacter::AABCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	IsAttacking = false;
	MaxCombo = 4;
	CurrentCombo = 0;
	CanNextCombo = false;
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

void AABCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	ensure(AnimInstance != nullptr);

	AnimInstance->OnMontageEnded.AddDynamic(this, &AABCharacter::OnAttackMontageEnded);

	AnimInstance->OnNextAttackCheck.AddUObject(this, &AABCharacter::OnNextAttackCheck);

}


// Called every frame
void AABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AABCharacter::OnAttack_Implementation()
{
	TryAttack();
}

void AABCharacter::OnNextAttackCheck()
{
	CanNextCombo = true;
}

bool AABCharacter::TryAttack()
{
	ABLOG_S(Warning);
	if (!IsAttacking)
	{
		IsAttacking = true;
		CurrentCombo = 1;
		CanNextCombo = false;
		AnimInstance->PlayAttackMontage();
		return true;
	}
	else
	{
		if (CurrentCombo >= 4)
			return false;

		if (CanNextCombo)
		{
			CanNextCombo = false;
			CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, 4);
			AnimInstance->JumpToAttackMontageSection(CurrentCombo);
			return true;
		}

		return false;
	}

}

void AABCharacter::OnJump_Implementation()
{
	ACharacter::Jump();
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

// Attack Montage를 Exit할 때 호출되는 함수
void AABCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	ABLOG_S(Warning);
	IsAttacking = false;
	CurrentCombo = 0;
	CanNextCombo = false;
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
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AABCharacter::OnJump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AABCharacter::OnAttack);
}