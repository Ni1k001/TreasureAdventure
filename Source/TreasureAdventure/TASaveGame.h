// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GraphicsSettingsStruct.h"
#include "SoundSettingsStruct.h"
#include "ControlsSettingsStruct.h"
#include "TASaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREADVENTURE_API UTASaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UTASaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Gameplay)
		int CurrentCoinCount;

	UPROPERTY(VisibleAnywhere, Category = Gameplay)
		int TotalCoinCount;

	UPROPERTY(VisibleAnywhere, Category = Gameplay)
		int TotalStarCount;

	UPROPERTY(VisibleAnywhere, Category = Gameplay)
		int LifeCount;

	UPROPERTY(VisibleAnywhere, Category = Level)
		TMap<FString, int32> LevelCollectedStarFlag;

	UPROPERTY(VisibleAnywhere, Category = Level)
		TMap<FString, bool> LevelAvailability;
};


UCLASS()
class TREASUREADVENTURE_API UTASaveSettings : public USaveGame
{
	GENERATED_BODY()

public:
	UTASaveSettings();

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Settings)
		FGraphicsSettingsStruct GraphicsSettings;

	UPROPERTY(VisibleAnywhere, Category = Settings)
		FSoundSettingsStruct SoundSettings;

	UPROPERTY(VisibleAnywhere, Category = Settings)
		FControlsSettingsStruct ControlsSettings;
};