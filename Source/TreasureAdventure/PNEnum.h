// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "PNEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class PNEnum : uint8
{
	EPrev 		UMETA(DisplayName = "Prev"),
	ENext		UMETA(DisplayName = "Next"),
};
