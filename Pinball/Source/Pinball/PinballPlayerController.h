// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PinballPlayerController.generated.h"

class AFlipper;
class APlunger;

/**
 * 
 */
UCLASS()
class PINBALL_API APinballPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

public:
	UFUNCTION(BlueprintCallable)
	void OnPressedLeftCtrl();

	UFUNCTION(BlueprintCallable)
	void OnReleasedLeftCtrl();

	UFUNCTION(BlueprintCallable)
	void OnPressedRightCtrl();

	UFUNCTION(BlueprintCallable)
	void OnReleasedRightCtrl();

	UFUNCTION(BlueprintCallable)
	void OnPressedPlunger();
	
	UFUNCTION(BlueprintCallable)
	void OnReleasedPlunger();

private:
	UFUNCTION(BlueprintCallable)
	void DetectFlippers();

	UFUNCTION(BlueprintCallable)
	void DetectPlunger();
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AFlipper*> LeftFlippers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AFlipper*> RightFlippers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlunger* Plunger;
};
