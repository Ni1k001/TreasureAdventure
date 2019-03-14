// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TreasureAdventureGameMode.h"
#include "TreasureAdventureCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerCharacter.h"

ATreasureAdventureGameMode::ATreasureAdventureGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}

	DefaultPawnClass = APlayerCharacter::StaticClass();
}

void ATreasureAdventureGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

void ATreasureAdventureGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> Widget)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (Widget != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), Widget);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}