// Copyright wonAdam 2021


#include "PressurePlate.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UPressurePlate::UPressurePlate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPressurePlate::BeginPlay()
{
	Super::BeginPlay();

	if (Door == nullptr) return;

	UActorComponent* OpenDoorComponent = Door->GetComponentByClass(UOpenDoor::StaticClass());
	if(OpenDoorComponent)
		OpenDoor = Cast<UOpenDoor>(OpenDoorComponent);

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UPressurePlate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerPawn == nullptr || OpenDoor == nullptr) return;

	TSet<AActor*> OverlappingActors;
	GetOwner()->GetOverlappingActors(OverlappingActors, GetWorld()->GetFirstPlayerController()->GetPawn()->StaticClass());
	
	if (GetOwner()->IsOverlappingActor(PlayerPawn) && OpenDoor != nullptr)
	{
		OpenDoor->OpenDoor();
	}
	else
	{
		OpenDoor->CloseDoor();
	}

}

