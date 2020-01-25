// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "SpecialBlock.generated.h"

UCLASS()
class TREASUREADVENTURE_API ASpecialBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpecialBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
		FTimeline Timeline;

	UPROPERTY(EditAnywhere, Category = Config)
		UCurveFloat* FloatCurve;

	UPROPERTY(EditAnywhere, Category = Config)
		FVector StartPosition;

	UPROPERTY(EditAnywhere, Category = Config)
		FVector EndPosition;

	UPROPERTY()
		float FloatCurveValue;

	UPROPERTY()
		float TimelineValue;

	UPROPERTY()
		TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0001", ClampMax = "5", UIMin = "0.0001", UIMax = "5"), Category = Config)
		float Speed;

public:
	UFUNCTION()
		void TimelineCallback(float Delta);

	UFUNCTION()
		void TimelineFinishedCallback();

	UFUNCTION()
		void PlayTimeline();

	UFUNCTION()
		void ReverseTimeline();

	UFUNCTION()
		FTimeline GetTimeline();
};
