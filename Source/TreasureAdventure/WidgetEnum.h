// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "WidgetEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class WidgetEnum : uint8
{
	ENone					UMETA(DisplayName = "None"),
	EMainMenuWidget 		UMETA(DisplayName = "MainMenuWidget"),
	ELevelLoadingWidget		UMETA(DisplayName = "LevelLoadingWidget"),
	EGameplayWidget 		UMETA(DisplayName = "GameplayWidget"),
	ELoadingScreenWidget 	UMETA(DisplayName = "LoadingScreenWidget"),
	EPauseMenuWidget 		UMETA(DisplayName = "PauseMenuWidget"),
};