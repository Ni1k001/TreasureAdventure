// Fill out your copyright notice in the Description page of Project Settings.

#include "TASaveGame.h"
#include "LMHESettingsEnum.h"

UTASaveGame::UTASaveGame()
{
	SaveSlotName = TEXT("Slot1");
	UserIndex = 0;

	CurrentCoinCount = 0;
	TotalCoinCount = 0;
	TotalStarCount = 0;
	LifeCount = 0;

	for (int i = 1; i <= 2; i++)
	{
		LevelCollectedStarFlag.Add("Level" + FString::FromInt(i), 0);
		LevelAvailability.Add("Level" + FString::FromInt(i), 0);
	}

	LevelAvailability["Level1"] = 1;
}

UTASaveSettings::UTASaveSettings()
{
	SaveSlotName = TEXT("Settings");
	UserIndex = 0;
}