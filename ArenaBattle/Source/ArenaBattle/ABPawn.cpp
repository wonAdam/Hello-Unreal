// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPawn.h"

// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);


	// AnimBlueprint'/Game/Animations/WarriorAnimBlueprint.WarriorAnimBlueprint'
	//Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	//static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/Animations/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	//if (WARRIOR_ANIM.Succeeded())
	//{
	//	Mesh->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	//}
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABPawn::OnUpDown_Implementation(float NewAxisValue)
{
	ABLOG(Warning, TEXT("OnUpDown: %.2f"), NewAxisValue);
	AddMovementInput(GetActorForwardVector(), NewAxisValue * 100.0f * GetWorld()->GetDeltaSeconds());
}

void AABPawn::OnLeftRight_Implementation(float NewAxisValue)
{
	ABLOG(Warning, TEXT("OnLeftRight: %.2f"), NewAxisValue);
	AddMovementInput(GetActorRightVector(), NewAxisValue * 100.0f * GetWorld()->GetDeltaSeconds());
}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABPawn::OnUpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABPawn::OnLeftRight);
}


void AABPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void AABPawn::PossessedBy(AController* NewControlller)
{
	Super::PossessedBy(NewControlller);
	ABLOG_S(Warning);
}

