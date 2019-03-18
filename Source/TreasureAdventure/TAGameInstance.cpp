// Fill out your copyright notice in the Description page of Project Settings.

#include "TAGameInstance.h"
#include "TASaveGame.h"
#include "LMHESettingsEnum.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

void UTAGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("INITIALIZE"));
	UGameInstance::Init();
}

void UTAGameInstance::OnStart()
{
	for (int i = 1; i <= 2; i++)
	{
		LevelCollectedStarFlag.Add("Level" + FString::FromInt(i), 0);
		LevelAvailability.Add("Level" + FString::FromInt(i), false);
	}

	LevelAvailability["Level1"] = true;

	LoadData();
}

void UTAGameInstance::UpdateCoinCount()
{
	CurrentCoinCount++;
	TotalCoinCount++;

	if (CurrentCoinCount == 100)
	{
		CurrentCoinCount = 0;
		UpdateLifeCount(1);
	}
}

int UTAGameInstance::GetCurrentCoinCount()
{
	return CurrentCoinCount;
}

int UTAGameInstance::GetTotalCoinCount()
{
	return TotalCoinCount;
}

void UTAGameInstance::UpdateStarCount(int StarID)
{
	CurrentStarCount++;
	TotalStarCount++;

	//FString LevelName = UGameplayStatics::GetCurrentLevelName(this);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *LevelName);

	LevelCollectedStarFlag[UGameplayStatics::GetCurrentLevelName(this)] += StarID;
}

int UTAGameInstance::GetCurrentStarCount()
{
	return CurrentStarCount;
}

int UTAGameInstance::GetTotalStarCount()
{
	return TotalStarCount;
}

void UTAGameInstance::UpdateLifeCount(int value)
{
	LifeCount += value;
}

int UTAGameInstance::GetLifeCount()
{
	return LifeCount;
}

void UTAGameInstance::SetCurrentLevel(FString level)
{
	CurrentLevel = level;
}

FString UTAGameInstance::GetCurrentLevel()
{
	return CurrentLevel;
}

void UTAGameInstance::SaveData()
{
	UTASaveGame* SaveGameInstance = Cast<UTASaveGame>(UGameplayStatics::CreateSaveGameObject(UTASaveGame::StaticClass()));
	
	SaveGameInstance->SaveSlotName = "Slot1";
	SaveGameInstance->UserIndex = 0;
	SaveGameInstance->TotalCoinCount = GetTotalCoinCount();
	SaveGameInstance->TotalStarCount = GetTotalStarCount();
	SaveGameInstance->LifeCount = GetLifeCount();
	SaveGameInstance->CurrentLevel = CurrentLevel;

	for (int i = 1; i <= 2; i++)
	{
		SaveGameInstance->LevelCollectedStarFlag.FindOrAdd("Level" + FString::FromInt(i));
		SaveGameInstance->LevelAvailability.FindOrAdd("Level" + FString::FromInt(i));

		SaveGameInstance->LevelCollectedStarFlag["Level" + FString::FromInt(i)] = LevelCollectedStarFlag["Level" + FString::FromInt(i)];
		SaveGameInstance->LevelAvailability["Level" + FString::FromInt(i)] = LevelAvailability["Level" + FString::FromInt(i)];
	}


	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);

	UE_LOG(LogTemp, Warning, TEXT("Saved Game"));
}

void UTAGameInstance::LoadData()
{
	UTASaveGame* LoadGameInstance = Cast<UTASaveGame>(UGameplayStatics::CreateSaveGameObject(UTASaveGame::StaticClass()));

	if (UGameplayStatics::DoesSaveGameExist(LoadGameInstance->SaveSlotName, 0))
	{
		LoadGameInstance = Cast<UTASaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
		if (LoadGameInstance)
		{
			TotalCoinCount = LoadGameInstance->TotalCoinCount;
			TotalStarCount = LoadGameInstance->TotalStarCount;
			LifeCount = LoadGameInstance->LifeCount;
			CurrentLevel = LoadGameInstance->CurrentLevel;

			UE_LOG(LogTemp, Warning, TEXT("Loaded Game"));

			UE_LOG(LogTemp, Warning, TEXT("Total Coin Count: %d"), GetTotalCoinCount());
			UE_LOG(LogTemp, Warning, TEXT("Total Star Count: %d"), GetTotalStarCount());
			UE_LOG(LogTemp, Warning, TEXT("Life Count: %d"), GetLifeCount());

			for (int i = 1; i <= 2; i++)
			{
				LevelCollectedStarFlag.FindOrAdd("Level" + FString::FromInt(i));
				LevelAvailability.FindOrAdd("Level" + FString::FromInt(i));

				LevelCollectedStarFlag["Level" + FString::FromInt(i)] = LoadGameInstance->LevelCollectedStarFlag["Level" + FString::FromInt(i)];
				LevelAvailability["Level" + FString::FromInt(i)] = LoadGameInstance->LevelAvailability["Level" + FString::FromInt(i)];

				UE_LOG(LogTemp, Warning, TEXT("%s Collected Star Flag: %d"), LevelCollectedStarFlag.FindKey(i), LevelCollectedStarFlag["Level" + FString::FromInt(i)]);
				UE_LOG(LogTemp, Warning, TEXT("%s Availability: %d"), LevelAvailability.FindKey(i), LevelAvailability["Level" + FString::FromInt(i)]);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Save game not existing"));
	}
}

void UTAGameInstance::SaveSettings(FGraphicsSettingsStruct GraphicsSettings, FSoundSettingsStruct SoundSettings, FControlsSettingsStruct ControlsSettings)
{
	UTASaveSettings* SaveSettingsInstance = Cast<UTASaveSettings>(UGameplayStatics::CreateSaveGameObject(UTASaveSettings::StaticClass()));

	SaveSettingsInstance->SaveSlotName = "Settings";
	SaveSettingsInstance->UserIndex = 0;
	SaveSettingsInstance->GraphicsSettings = GraphicsSettings;
	SaveSettingsInstance->SoundSettings = SoundSettings;
	SaveSettingsInstance->ControlsSettings = ControlsSettings;

	UGameplayStatics::SaveGameToSlot(SaveSettingsInstance, SaveSettingsInstance->SaveSlotName, SaveSettingsInstance->UserIndex);

	UE_LOG(LogTemp, Warning, TEXT("Saved Settings"));
}

void UTAGameInstance::LoadSettings(FGraphicsSettingsStruct &GraphicsSettings, FSoundSettingsStruct &SoundSettings, FControlsSettingsStruct &ControlsSettings)
{
	UTASaveSettings* LoadSettingsInstance = Cast<UTASaveSettings>(UGameplayStatics::CreateSaveGameObject(UTASaveSettings::StaticClass()));

	if (UGameplayStatics::DoesSaveGameExist(LoadSettingsInstance->SaveSlotName, 0))
	{
		LoadSettingsInstance = Cast<UTASaveSettings>(UGameplayStatics::LoadGameFromSlot(LoadSettingsInstance->SaveSlotName, LoadSettingsInstance->UserIndex));
		if (LoadSettingsInstance)
		{
			GraphicsSettings = LoadSettingsInstance->GraphicsSettings;
			SoundSettings = LoadSettingsInstance->SoundSettings;
			ControlsSettings = LoadSettingsInstance->ControlsSettings;

			UE_LOG(LogTemp, Warning, TEXT("Loaded Settings"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Save settings not existing"));
	}
}