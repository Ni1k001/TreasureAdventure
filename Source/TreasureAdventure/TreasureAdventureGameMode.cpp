// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TreasureAdventureGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerCharacter.h"
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