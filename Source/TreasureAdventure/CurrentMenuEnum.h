// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "CurrentMenuEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class CurrentMenuEnum : uint8
{
	EMainMenu 	UMETA(DisplayName = "MainMenu"),
	ESettings 	UMETA(DisplayName = "Settings"),
};
