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

	UFUNCTION(BlueprintCallable, Category = "UMG")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> Widget);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
		UUserWidget* CurrentWidget;
};



