// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "LMHESettingsEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class LMHESettingsEnum : uint8
{
	ELow 		UMETA(DisplayName = "Low"),
	EMedium 	UMETA(DisplayName = "Medium"),
	EHigh 		UMETA(DisplayName = "High"),
	EEpic 		UMETA(DisplayName = "Epic"),
};
