// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"
#include "ABAnimInstance.h"
#include "ABWeapon.h"
#include "ABCharacterStatComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/WidgetComponent.h"
#include "ABCharacterWidget.h"

// Sets default values
AABCharacter::AABCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CharacterStat = CreateDefaultSubobject<UABCharacterStatComponent>(TEXT("Stat"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar Wdiget"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	HPBarWidget->SetupAttachment(GetMesh());

	//HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	//HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	//// WidgetBlueprint'/Game/UI/UI_HPBar.UI_HPBar'
	//static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/UI/UI_HPBar.UI_HPBar_C"));
	//if (UI_HUD.Succeeded())
	//{
	//	HPBarWidget->SetWidgetClass(UI_HUD.Class);
	//	HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	//}

	IsAttacking = false;
	MaxCombo = 4;
	CurrentCombo = 0;
	CanNextCombo = false;

	AttackRange = 200.0f;
	AttackRadius = 50.0f;
}

float AABCharacter::TakeDamage(float DamageAmount,
	struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator,
	AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ABLOG(Warning, TEXT("Actor: %s took Damage %f"), *GetName(), FinalDamage);

	CharacterStat->SetDamage(FinalDamage);
	return FinalDamage;
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

	auto CharacterWidget = Cast<UABCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (CharacterWidget != nullptr)
	{
		CharacterWidget->BindCharacterStat(CharacterStat);
	}
}

void AABCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	ABCHECK(AnimInstance != nullptr);

	AnimInstance->OnMontageEnded.AddDynamic(this, &AABCharacter::OnAttackMontageEnded);

	AnimInstance->OnNextAttackCheck.AddUObject(this, &AABCharacter::OnNextAttackCheck);
	AnimInstance->OnAttackHitCheck.AddUObject(this, &AABCharacter::OnAttackHitCheck);

	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		ABLOG(Warning, TEXT("OnHPIsZero"));
		AnimInstance->SetDeadAnim();
		SetActorEnableCollision(false);
		});

	// < UE 4.21
	//auto CharacterWidget = Cast<UABCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	//if (CharacterWidget != nullptr)
	//{
	//	CharacterWidget->BindCharacterStat(CharacterStat);
	//}
}

void AABCharacter::SetWeapon_Implementation(AABWeapon* NewWeapon)
{
	ABCHECK(NewWeapon != nullptr && CurrentWeapon == nullptr);

	FName WeaponSocket(TEXT("hand_rSocket"));
	if (NewWeapon != nullptr)
	{
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);
		CurrentWeapon = NewWeapon;
	}
}

bool AABCharacter::CanSetWeapon_Implementation()
{
	return CurrentWeapon == nullptr;
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

void AABCharacter::OnAttackHitCheck()
{
	FCollisionQueryParams MultiParams(NAME_None, false, this);
	TArray<FHitResult> MultiHitResults;
	GetWorld()->SweepMultiByChannel(
		MultiHitResults,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, // Attack TraceChannel
		FCollisionShape::MakeSphere(50.0f),
		MultiParams
	);

	for (const auto& SingleResult : MultiHitResults)
	{
		if (SingleResult.Actor.IsValid())
		{
			ABLOG(Warning, TEXT("Multi Hit Actor Name: %s"), *SingleResult.Actor->GetName());
		
			FDamageEvent DamageEvent;
			SingleResult.Actor->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);
		}
	}

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = MultiHitResults.Num() > 0 ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(
		GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor, 
		false,
		DebugLifeTime
	);
#endif // ENABLE_DRAW_DEBUG
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