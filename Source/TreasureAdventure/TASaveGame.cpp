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
	LifeCount = 3;
	CurrentLevel = "Level1";

	/*****************************************************************/
	//LevelCollectedStarFlag.Add("LevelTest", 0);
	//LevelAvailability.Add("LevelTest", true);
	/*****************************************************************/

	for (int i = 1; i <= MapCount; i++)
	{
		LevelCollectedStarFlag.Add("Level" + FString::FromInt(i), 0);
		LevelAvailability.Add("Level" + FString::FromInt(i), false);
	}

	LevelAvailability["Level1"] = true;
}

UTASaveSettings::UTASaveSettings()
{
	SaveSlotName = TEXT("Settings");
	UserIndex = 0;
}