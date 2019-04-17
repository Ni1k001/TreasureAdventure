// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TAPlayerController.generated.h"

/**
 *  
 */
UCLASS()
class TREASUREADVENTURE_API ATAPlayerController : public APlayerController
{
	GENERATED_BODY()

	ATAPlayerController();

public:
	UPROPERTY(Transient, BlueprintReadOnly)
		bool bIsUsingGamepad;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool bResetGamepadDetectionAfterNoInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bResetGamepadDetectionAfterNoInput"))
		float GamepadTimeout;

	virtual bool InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad) override;
	virtual bool InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad) override;
	virtual void PlayerTick(float DeltaTime) override;

protected:
	FORCEINLINE void _UpdateGamepad(bool bGamepad)
	{
		bIsUsingGamepad = bGamepad;
		if (bGamepad)
		{
			LastGamepadInputTime = GetWorld()->TimeSeconds;
		}
	}

	UPROPERTY(Transient, BlueprintReadOnly)
		float LastGamepadInputTime;
};
