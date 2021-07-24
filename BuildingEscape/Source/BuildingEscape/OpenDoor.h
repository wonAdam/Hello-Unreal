// Copyright wonAdam 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

UENUM(BlueprintType)
enum class DoorState : uint8 
{ 
	Opened, 
	Closed, 
	Opening, 
	Closing,
	ForceClosing
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION()
	void OpenDoor();

	UFUNCTION()
	void CloseDoor();

private:
	UFUNCTION()
	bool OpeningDoor(float DeltaTime);

	UFUNCTION()
	bool ClosingDoor(float DeltaTime);

	UFUNCTION()
	void CountOpenedDuration(float DeltaTime);

public:
	UPROPERTY(VisibleAnywhere)
	float OpenAngleZ;

	UPROPERTY(VisibleAnywhere)
	float CloseAngleZ;

	UPROPERTY(EditAnywhere)
	float OpeningAngleDelta = 90.0f;

	UPROPERTY(EditAnywhere)
	float OpeningInterval = 5.0f;

	UPROPERTY(EditAnywhere)
	float ClosingInterval = 5.0f;

	UPROPERTY(VisibleAnywhere)
	float CurrentTime = 0.0f;

	UPROPERTY(VisibleAnywhere)
	DoorState State = DoorState::Closed;

	UPROPERTY(VisibleAnywhere)
	float OpenDuration = 2.0f;

	UPROPERTY(VisibleAnywhere)
	float CountAfterOpened = 0.0f;
};
