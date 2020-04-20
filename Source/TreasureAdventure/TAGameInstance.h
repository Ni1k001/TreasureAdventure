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
	UPROPERTY(BlueprintGetter = GetCurrentCoinCount, Category = "TreasureAdventure|Collectable")
		int CurrentCoinCount;

	UPROPERTY(BlueprintGetter = GetTotalCoinCount, Category = "TreasureAdventure|Collectable")
		int TotalCoinCount;
	
	//UPROPERTY(BlueprintGetter = GetbControllerMode, BlueprintSetter = SetbControllerMode, Category = "TreasureAdventure|Controller")
		int CurrentStarCount;
	
	UPROPERTY(BlueprintGetter = GetTotalStarCount, Category = "TreasureAdventure|Collectable")
		int TotalStarCount;
	
	UPROPERTY(BlueprintGetter = GetLifeCount, Category = "TreasureAdventure|Health")
		int LifeCount;
	
	UPROPERTY(/*BlueprintGetter = GetCurrentLevel,*/ BlueprintSetter = SetCurrentLevel, Category = "TreasureAdventure|Level")
		FString CurrentLevel;
	
	UPROPERTY(BlueprintGetter = GetCurrentStreamingLevel, BlueprintSetter = SetCurrentStreamingLevel, Category = "TreasureAdventure|Level")
		FName CurrentStreamingLevel;

	UPROPERTY(BlueprintGetter = GetbControllerType, BlueprintSetter = SetbControllerType, Category = "TreasureAdventure|Controller")
	bool bControllerType;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Level)
	TMap<FString, int32> LevelCollectedStarFlag;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Level)
	TMap<FString, bool> LevelAvailability;

	virtual void Init() override;

	virtual void OnStart();

	UFUNCTION()
		void UpdateCoinCount();

	UFUNCTION(BlueprintGetter, Category = "TreasureAdventure|Collectable")
		int GetCurrentCoinCount();

	UFUNCTION(BlueprintGetter, Category = "TreasureAdventure|Collectable")
		int GetTotalCoinCount();

	UFUNCTION()
		void UpdateStarCount(int StarID);

	UFUNCTION()
		int GetCurrentStarCount();

	UFUNCTION(BlueprintGetter, Category = "TreasureAdventure|Collectable")
		int GetTotalStarCount();

	UFUNCTION()
		void SetTotalStarCount(int InTotalStarCount);

	UFUNCTION()
		void UpdateLifeCount(int value);

	UFUNCTION(BlueprintGetter, Category = "TreasureAdventure|Health")
		int GetLifeCount();

	UFUNCTION(BlueprintSetter, Category = "TreasureAdventure|Level")
		void SetCurrentLevel(FString InCurrentLevel);

	UFUNCTION(BlueprintCallable, Category = "TreasureAdventure|Level")
		FString GetCurrentLevel();

	UFUNCTION(BlueprintSetter, Category = "TreasureAdventure|Level")
		void SetCurrentStreamingLevel(FName InCurrentStreamingLevel);

	UFUNCTION(BlueprintGetter, Category = "TreasureAdventure|Level")
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

	UFUNCTION(BlueprintCallable, Category = "TreasureAdventure")
		static FString GetAppVersion();

	UFUNCTION(BlueprintSetter, Category = "TreasureAdventure|Controller")
		void SetbControllerType(bool InBControllerMode);

	UFUNCTION(BlueprintGetter, Category = "TreasureAdventure|Controller")
		bool GetbControllerType();

private:
	int MapCount = 4;
};