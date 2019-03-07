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
	int CurrentCoinCount = 0;
	int TotalCoinCount = 0;
	int CurrentStarCount = 0;
	int TotalStarCount = 0;
	int LifeCount = 3;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Level)
	TMap<FString, int32> LevelCollectedStarFlag;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Level)
	TMap<FString, bool> LevelAvailability;

	virtual void Init() override;

	virtual void OnStart();

	UFUNCTION()
		void UpdateCoinCount();

	UFUNCTION()
		int GetCurrentCoinCount();

	UFUNCTION()
		int GetTotalCoinCount();

	UFUNCTION()
		void UpdateStarCount(int StarID);

	UFUNCTION()
		int GetCurrentStarCount();

	UFUNCTION()
		int GetTotalStarCount();

	UFUNCTION()
		void UpdateLifeCount(int value);

	UFUNCTION()
		int GetLifeCount();

	UFUNCTION(BlueprintCallable)
		void SaveData();

	UFUNCTION(BlueprintCallable)
		void LoadData();

	UFUNCTION(BlueprintCallable)
		void LoadSettings(FGraphicsSettingsStruct &GraphicsSettings, FSoundSettingsStruct &SoundSettings, FControlsSettingsStruct &ControlsSettings);

	UFUNCTION(BlueprintCallable)
		void SaveSettings(FGraphicsSettingsStruct GraphicsSettings, FSoundSettingsStruct SoundSettings, FControlsSettingsStruct ControlsSettings);
};