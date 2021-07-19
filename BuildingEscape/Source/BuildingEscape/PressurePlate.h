// Copyright wonAdam 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.h"
#include "Engine/TriggerBox.h"
#include "Engine/StaticMeshActor.h"
#include "PressurePlate.generated.h"	


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UPressurePlate : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPressurePlate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere)
		AStaticMeshActor* Door;

	UPROPERTY(VisibleAnywhere)
		UOpenDoor* OpenDoor;

	UPROPERTY(VisibleAnywhere)
		AActor* PlayerPawn;
};
