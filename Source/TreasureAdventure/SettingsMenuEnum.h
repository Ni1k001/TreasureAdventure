// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "SettingsMenuEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class SettingsMenuEnum : uint8
{
	EGraphics 		UMETA(DisplayName = "Graphics"),
	ESound 			UMETA(DisplayName = "Sound"),
	EControls 		UMETA(DisplayName = "Controls"),
};
