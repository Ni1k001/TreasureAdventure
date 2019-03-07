// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "ControlsSettingsStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FControlsSettingsStruct
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MouseSensitivity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool MouseInvert = false;
};