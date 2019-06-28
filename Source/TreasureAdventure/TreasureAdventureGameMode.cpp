// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TreasureAdventureGameMode.h"
#include "TreasureAdventureCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerCharacter.h"

ATreasureAdventureGameMode::ATreasureAdventureGameMode()
{
	// set default pawn class
	DefaultPawnClass = APlayerCharacter::StaticClass();
}

void ATreasureAdventureGameMode::BeginPlay()
{
	Super::BeginPlay();
}