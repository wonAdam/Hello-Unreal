// Copyright wonAdam 2021


#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	CloseAngleZ = GetOwner()->GetActorRotation().Yaw;
	OpenAngleZ = CloseAngleZ + OpeningAngleDelta;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (State == DoorState::Opening)
	{
		OpeningDoor(DeltaTime);
	}
	else if (State == DoorState::Closing ||
		State == DoorState::ForceClosing)
	{
		ClosingDoor(DeltaTime);
	}
	if (State == DoorState::Opened)
	{
		CountOpenedDuration(DeltaTime);
	}
	else
	{
		CountAfterOpened = 0.f;
	}

}

void UOpenDoor::OpenDoor()
{
	if (State == DoorState::Opening ||
		State == DoorState::Opened ||
		State == DoorState::ForceClosing)
		return;

	State = DoorState::Opening; 
	float DiffToTargetAngle = FMath::Abs(OpenAngleZ - GetOwner()->GetActorRotation().Yaw);
	CurrentTime = OpeningInterval * (1 - DiffToTargetAngle / OpeningAngleDelta);
}

void UOpenDoor::CloseDoor()
{
	if (State == DoorState::Closing || 
		State == DoorState::Closed)
		return;

	State = DoorState::Closing;
	float DiffToTargetAngle = FMath::Abs(CloseAngleZ - GetOwner()->GetActorRotation().Yaw);
	CurrentTime = ClosingInterval * (1 - DiffToTargetAngle / OpeningAngleDelta);
}

bool UOpenDoor::OpeningDoor(float DeltaTime)
{
	CurrentTime = FMath::Clamp(DeltaTime + CurrentTime, 0.0f, OpeningInterval);
	float TargetAngle = FMath::Lerp(CloseAngleZ, OpenAngleZ, CurrentTime / OpeningInterval);

	FRotator NewRotation = GetOwner()->GetActorRotation();
	NewRotation.Yaw = TargetAngle;
	GetOwner()->SetActorRotation(NewRotation);

	if (CurrentTime == OpeningInterval)
	{
		State = DoorState::Opened;
		CurrentTime = 0.0f;
		return true;
	}
	else
	{
		return false;
	}
}

bool UOpenDoor::ClosingDoor(float DeltaTime)
{
	CurrentTime = FMath::Clamp(DeltaTime + CurrentTime, 0.0f, ClosingInterval);
	float TargetAngle = FMath::Lerp(OpenAngleZ, CloseAngleZ, CurrentTime / ClosingInterval);

	FRotator NewRotation = GetOwner()->GetActorRotation();
	NewRotation.Yaw = TargetAngle;
	GetOwner()->SetActorRotation(NewRotation);

	if (CurrentTime == ClosingInterval)
	{
		State = DoorState::Closed;
		CurrentTime = 0.0f;
		return true;
	}
	else
	{
		return false;
	}
}

void UOpenDoor::CountOpenedDuration(float DeltaTime)
{
	CountAfterOpened += DeltaTime;

	if (CountAfterOpened > OpenDuration)
	{
		State = DoorState::ForceClosing;
		CountAfterOpened = 0.0f;
	}
}

