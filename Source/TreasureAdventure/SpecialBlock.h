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

	UPROPERTY(EditAnywhere, Category = Config, meta = (EditCondition = "bIsMovable"))
		FVector StartPosition;

	UPROPERTY(EditAnywhere, Category = Config, meta = (EditCondition = "bIsMovable"))
		FVector EndPosition;

	UPROPERTY(EditAnywhere, Category = Config, meta = (EditCondition = "bIsRotatable"))
		FRotator StartRotation;

	UPROPERTY(EditAnywhere, Category = Config)
		FRotator EndRotation;

	UPROPERTY(EditAnywhere, Category = Config, meta = (EditCondition = "bIsFullRotation"))
		FRotator RotationAngle;

	UPROPERTY()
		float FloatCurveValue;

	UPROPERTY()
		float TimelineValue;

	UPROPERTY()
		TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0001", ClampMax = "5", UIMin = "0.0001", UIMax = "5"), Category = Config)
		float Speed;

	UPROPERTY(EditAnywhere, Category = Config)
		bool bIsMovable;

	UPROPERTY(EditAnywhere, Category = Config)
		bool bIsRotatable;

	UPROPERTY(EditAnywhere, Category = Config, meta = (EditCondition = "bIsRotatable"))
		bool bIsFullRotation;


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

#if WITH_EDITOR
	virtual bool CanEditChange(const UProperty* InProperty) const override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
#endif
};
