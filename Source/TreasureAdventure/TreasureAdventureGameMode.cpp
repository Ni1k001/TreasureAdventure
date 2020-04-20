// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TreasureAdventureGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerCharacter.h"
#include "TAGameInstance.h"
#include "EngineGlobals.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

ATreasureAdventureGameMode::ATreasureAdventureGameMode()
{
	// set default pawn class
	DefaultPawnClass = APlayerCharacter::StaticClass();
}

void ATreasureAdventureGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ATreasureAdventureGameMode::TEST()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("This is a test message."));
}

void ATreasureAdventureGameMode::UnlockAllLevels()
{
	UTAGameInstance* GI = Cast<UTAGameInstance>(GetGameInstance());

	for (int i = 1; i <= 4; i++)
	{
		GI->LevelAvailability["Level" + FString::FromInt(i)] = true;
	}

	GI->SetTotalStarCount(999);
}

void ATreasureAdventureGameMode::ClearChanges()
{
	UTAGameInstance* GI = Cast<UTAGameInstance>(GetGameInstance());

	GI->LoadData();
}