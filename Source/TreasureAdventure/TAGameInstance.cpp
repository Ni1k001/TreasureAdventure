// Fill out your copyright notice in the Description page of Project Settings.

#include "TAGameInstance.h"
#include "TASaveGame.h"
#include "LMHESettingsEnum.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine.h"

void UTAGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("INITIALIZE"));
	UGameInstance::Init();
}

void UTAGameInstance::OnStart()
{
	CurrentCoinCount = 0;
	TotalCoinCount = 0;
	CurrentStarCount = 0;
	TotalStarCount = 0;
	LifeCount = 3;
	CurrentLevel = "Level1";
	CurrentStreamingLevel = "L_MainMenu";
	bControllerType = false;

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

	for (auto& Elem : LevelCollectedStarFlag)
	{
		if (GetCurrentLevel() == Elem.Key)
			LevelCollectedStarFlag[GetCurrentLevel()] += StarID;
	}
}

int UTAGameInstance::GetCurrentStarCount()
{
	return CurrentStarCount;
}

int UTAGameInstance::GetTotalStarCount()
{
	return TotalStarCount;
}

void UTAGameInstance::SetTotalStarCount(int InTotalStarCount)
{
	TotalStarCount = InTotalStarCount;
}

void UTAGameInstance::UpdateLifeCount(int value)
{
	LifeCount += value;
}

int UTAGameInstance::GetLifeCount()
{
	return LifeCount;
}

void UTAGameInstance::SetCurrentLevel(FString InCurrentLevel)
{
	CurrentLevel = InCurrentLevel;
}

FString UTAGameInstance::GetCurrentLevel()
{
	return CurrentLevel;
}

void UTAGameInstance::SetCurrentStreamingLevel(FName InCurrentStreamingLevel)
{
	CurrentStreamingLevel = InCurrentStreamingLevel;
	OnLevelStreamingChange();
}

FName UTAGameInstance::GetCurrentStreamingLevel()
{
	return CurrentStreamingLevel;
}

void UTAGameInstance::SaveData()
{
	UTASaveGame* SaveGameInstance = Cast<UTASaveGame>(UGameplayStatics::CreateSaveGameObject(UTASaveGame::StaticClass()));
	
	SaveGameInstance->SaveSlotName = "Slot1";
	SaveGameInstance->UserIndex = 0;
	SaveGameInstance->CurrentCoinCount = GetCurrentCoinCount();
	SaveGameInstance->TotalCoinCount = GetTotalCoinCount();
	SaveGameInstance->TotalStarCount = GetTotalStarCount();
	SaveGameInstance->LifeCount = GetLifeCount();
	SaveGameInstance->CurrentLevel = CurrentLevel;
	SaveGameInstance->bControllerType = GetbControllerType();

	for (int i = 1; i <= MapCount; i++)
	{
		SaveGameInstance->LevelCollectedStarFlag.FindOrAdd("Level" + FString::FromInt(i));
		SaveGameInstance->LevelAvailability.FindOrAdd("Level" + FString::FromInt(i));

		SaveGameInstance->LevelCollectedStarFlag["Level" + FString::FromInt(i)] = LevelCollectedStarFlag["Level" + FString::FromInt(i)];
		SaveGameInstance->LevelAvailability["Level" + FString::FromInt(i)] = LevelAvailability["Level" + FString::FromInt(i)];
	}


	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);

	UE_LOG(LogTemp, Warning, TEXT("Game saved"));
}

void UTAGameInstance::LoadData()
{
	UTASaveGame* LoadGameInstance = Cast<UTASaveGame>(UGameplayStatics::CreateSaveGameObject(UTASaveGame::StaticClass()));

	if (UGameplayStatics::DoesSaveGameExist(LoadGameInstance->SaveSlotName, 0))
	{
		LoadGameInstance = Cast<UTASaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
		if (LoadGameInstance)
		{
			CurrentCoinCount = LoadGameInstance->CurrentCoinCount;
			TotalCoinCount = LoadGameInstance->TotalCoinCount;
			TotalStarCount = LoadGameInstance->TotalStarCount;
			LifeCount = LoadGameInstance->LifeCount;
			CurrentLevel = LoadGameInstance->CurrentLevel;
			bControllerType = LoadGameInstance->bControllerType;

			UE_LOG(LogTemp, Warning, TEXT("Game loaded"));

			UE_LOG(LogTemp, Warning, TEXT("Total Coin Count: %d"), GetTotalCoinCount());
			UE_LOG(LogTemp, Warning, TEXT("Total Star Count: %d"), GetTotalStarCount());
			UE_LOG(LogTemp, Warning, TEXT("Life Count: %d"), GetLifeCount());

			for (int i = 1; i <= MapCount; i++)
			{
				LevelCollectedStarFlag.FindOrAdd("Level" + FString::FromInt(i));
				LevelAvailability.FindOrAdd("Level" + FString::FromInt(i));

				LevelCollectedStarFlag["Level" + FString::FromInt(i)] = LoadGameInstance->LevelCollectedStarFlag["Level" + FString::FromInt(i)];
				LevelAvailability["Level" + FString::FromInt(i)] = LoadGameInstance->LevelAvailability["Level" + FString::FromInt(i)];
			}

			UE_LOG(LogTemp, Warning, TEXT("LEVELS COLLECTED STARS:"));

			for (auto& LCSF : LevelCollectedStarFlag)
			{
				FString Key = LCSF.Key;
				int32 Value = LCSF.Value;

				UE_LOG(LogTemp, Warning, TEXT("%s: %d"), *Key, Value);
			}

			UE_LOG(LogTemp, Warning, TEXT("LEVELS AVAILABILITY:"));

			for (auto& LAF : LevelAvailability)
			{
				FString Key = LAF.Key;
				int32 Value = LAF.Value;

				UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *Key, (Value ? TEXT("True") : TEXT("False")));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game save does not exist"));
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

	UE_LOG(LogTemp, Warning, TEXT("Settings saved"));
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

			UE_LOG(LogTemp, Warning, TEXT("Settings loaded"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Settings save does not exist"));
	}
}

void UTAGameInstance::ResetSave()
{
	CurrentCoinCount = 0;
	TotalCoinCount = 0;
	TotalStarCount = 0;
	LifeCount = 3;
	CurrentLevel = "Level1";
	bControllerType = false;

	for (int i = 1; i <= MapCount; i++)
	{
		LevelCollectedStarFlag["Level" + FString::FromInt(i)] = 0;
		LevelAvailability["Level" + FString::FromInt(i)] = false;
	}

	LevelAvailability["Level1"] = true;

	UE_LOG(LogTemp, Warning, TEXT("Game save reseted"))
}

FString UTAGameInstance::GetAppVersion()
{
	FString AppVersion;

	GConfig->GetString(TEXT("/Script/EngineSettings.GeneralProjectSettings"), TEXT("ProjectVersion"), AppVersion, GGameIni);

	return AppVersion;
}

void UTAGameInstance::SetbControllerType(bool InBControllerMode)
{
	bControllerType = InBControllerMode;
}

bool UTAGameInstance::GetbControllerType()
{
	return bControllerType;
}