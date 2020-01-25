// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GraphicsSettingsStruct.h"
#include "SoundSettingsStruct.h"
#include "ControlsSettingsStruct.h"
#include "TAGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREADVENTURE_API UTAGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	int CurrentCoinCount;
	int TotalCoinCount;
	int CurrentStarCount;
	int TotalStarCount;
	int LifeCount;
	FString CurrentLevel;
	FName CurrentStreamingLevel;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Level)
	TMap<FString, int32> LevelCollectedStarFlag;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Level)
	TMap<FString, bool> LevelAvailability;

	virtual void Init() override;

	virtual void OnStart();

	UFUNCTION()
		void UpdateCoinCount();

	UFUNCTION(BlueprintCallable)
		int GetCurrentCoinCount();

	UFUNCTION(BlueprintCallable)
		int GetTotalCoinCount();

	UFUNCTION()
		void UpdateStarCount(int StarID);

	UFUNCTION()
		int GetCurrentStarCount();

	UFUNCTION(BlueprintCallable)
		int GetTotalStarCount();

	UFUNCTION()
		void UpdateLifeCount(int value);

	UFUNCTION(BlueprintCallable)
		int GetLifeCount();

	UFUNCTION(BlueprintCallable)
		void SetCurrentLevel(FString level);

	UFUNCTION(BlueprintCallable)
		FString GetCurrentLevel();

	UFUNCTION(BlueprintCallable)
		void SetCurrentStreamingLevel(FName level);

	UFUNCTION(BlueprintCallable)
		FName GetCurrentStreamingLevel();

	UFUNCTION(BlueprintImplementableEvent)
		void OnLevelStreamingChange();

	UFUNCTION(BlueprintCallable)
		void SaveData();

	UFUNCTION(BlueprintCallable)
		void LoadData();

	UFUNCTION(BlueprintCallable)
		void SaveSettings(FGraphicsSettingsStruct GraphicsSettings, FSoundSettingsStruct SoundSettings, FControlsSettingsStruct ControlsSettings);

	UFUNCTION(BlueprintCallable)
		void LoadSettings(FGraphicsSettingsStruct &GraphicsSettings, FSoundSettingsStruct &SoundSettings, FControlsSettingsStruct &ControlsSettings);

	UFUNCTION(BlueprintCallable)
		void ResetSave();

	UFUNCTION(BlueprintCallable)
		static FString GetAppVersion();

private:
	int MapCount = 4;
};