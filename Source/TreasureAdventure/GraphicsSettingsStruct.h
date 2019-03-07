// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LMHESettingsEnum.h"
#include "Engine/UserDefinedStruct.h"
#include "GraphicsSettingsStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FGraphicsSettingsStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ResolutionIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		LMHESettingsEnum AntiAliasing = LMHESettingsEnum::EEpic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		LMHESettingsEnum PostProcessing = LMHESettingsEnum::EEpic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		LMHESettingsEnum ShadowsQuality = LMHESettingsEnum::EEpic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		LMHESettingsEnum TexturesQuality = LMHESettingsEnum::EEpic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		LMHESettingsEnum EffectsQuality = LMHESettingsEnum::EEpic;
};
