// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "SoundSettingsStruct.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FSoundSettingsStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MasterVolume = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SFXVolume = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MusicVolume = 0.f;
};
