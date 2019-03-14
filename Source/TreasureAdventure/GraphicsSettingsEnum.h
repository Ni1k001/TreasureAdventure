// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "GraphicsSettingsEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class GraphicsSettingsEnum : uint8
{
	EAntiAliasing 		UMETA(DisplayName = "AntiAliasing"),
	EPostProcessing 	UMETA(DisplayName = "PostProcessing"),
	EShadowsQuality 	UMETA(DisplayName = "ShadowsQuality"),
	ETexturesQuality 	UMETA(DisplayName = "TexturesQuality"),
	EEffectsQuality 	UMETA(DisplayName = "EffectsQuality"),
};
