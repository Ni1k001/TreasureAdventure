// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "TreasureAdventureGameMode.generated.h"

UCLASS(minimalapi)
class ATreasureAdventureGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATreasureAdventureGameMode();

	UFUNCTION(Exec)
		void TEST();

	UFUNCTION(Exec)
		void UnlockAllLevels();

	UFUNCTION(Exec)
		void ClearChanges();

protected:
	virtual void BeginPlay() override;
};



