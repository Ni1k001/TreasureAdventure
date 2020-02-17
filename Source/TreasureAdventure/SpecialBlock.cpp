// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecialBlock.h"
#include "Engine.h"
#include "TreasureAdventure.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpecialBlock::ASpecialBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(false);

	RootComponent = Mesh;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComp->SetBoxExtent(FVector(40.f, 40.f, 40.f));
	CollisionComp->SetupAttachment(RootComponent);
	CollisionComp->SetHiddenInGame(true);

	Speed = 1;

	bIsMovable = true;
	bIsRotatable = false;
	bIsFullRotation = false;
	RotationAngle = FRotator::ZeroRotator;
}

// Called when the game starts or when spawned
void ASpecialBlock::BeginPlay()
{
	Super::BeginPlay();

	if (FloatCurve)
	{
		FOnTimelineFloat onTimelineCallback;
		FOnTimelineEventStatic onTimelineFinishedCallback;

		onTimelineCallback.BindUFunction(this, FName{ TEXT("TimelineCallback") });
		onTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("TimelineFinishedCallback") });
		Timeline.AddInterpFloat(FloatCurve, onTimelineCallback);
		Timeline.SetTimelineFinishedFunc(onTimelineFinishedCallback);
		Timeline.SetPlayRate(Speed);

		if (bIsFullRotation)
			EndRotation = StartRotation + RotationAngle;
	}
}

// Called every frame
void ASpecialBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);
}

void ASpecialBlock::TimelineCallback(float Delta)
{
	if (Mesh)
	{
		if (bIsMovable && !bIsRotatable)
			Mesh->SetRelativeLocation(FMath::Lerp(StartPosition, EndPosition, Delta));
		else if (!bIsMovable && bIsRotatable)
			Mesh->SetRelativeRotation(FQuat::SlerpFullPath(FQuat(StartRotation), FQuat(EndRotation), Delta));
		else if (bIsMovable && bIsRotatable)
			Mesh->SetRelativeLocationAndRotation(FMath::Lerp(StartPosition, EndPosition, Delta), FMath::Lerp(FQuat(StartRotation), FQuat(EndRotation), Delta));
	}
}

void ASpecialBlock::TimelineFinishedCallback()
{
	if (bIsMovable && !bIsRotatable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Test 1"));
		if (GetActorLocation() == EndPosition)
		{
			UE_LOG(LogTemp, Warning, TEXT("Test 1-1"));
			Swap(StartPosition, EndPosition);

			Timeline.SetPlaybackPosition(0.f, false);
		}
	}
	else if (!bIsMovable && bIsRotatable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Test 2"));
		if (GetActorRotation() != StartRotation)
		{
			UE_LOG(LogTemp, Warning, TEXT("Test 2-1"));
			if (bIsFullRotation)
			{
				UE_LOG(LogTemp, Warning, TEXT("Test 2-2"));
				StartRotation = EndRotation;
				EndRotation = EndRotation + RotationAngle;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Test 2-3"));
				Swap(StartRotation, EndRotation);
			}

			Timeline.SetPlaybackPosition(0.f, false);
		}
	}
	else if (bIsMovable && bIsRotatable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Test 3"));
		if (GetActorLocation() == EndPosition && GetActorRotation() != StartRotation)
		{
			Swap(StartPosition, EndPosition);

			if (bIsFullRotation)
			{
				StartRotation = EndRotation;
				EndRotation = EndRotation + RotationAngle;
			}
			else
				Swap(StartRotation, EndRotation);

			Timeline.SetPlaybackPosition(0.f, false);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), GetActorRotation().Roll, GetActorRotation().Pitch, GetActorRotation().Yaw);
}

void ASpecialBlock::PlayTimeline()
{
	Timeline.Play();
}

void ASpecialBlock::ReverseTimeline()
{
	Timeline.Reverse();
}

FTimeline ASpecialBlock::GetTimeline()
{
	return Timeline;
}

#if WITH_EDITOR
bool ASpecialBlock::CanEditChange(const UProperty* InProperty) const
{
	const bool ParentVal = Super::CanEditChange(InProperty);

	if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(ASpecialBlock, EndRotation))
	{
		return (bIsRotatable == true && bIsFullRotation != true);
	}

	return ParentVal;
}

void ASpecialBlock::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (!bIsRotatable)
		bIsFullRotation = false;
}
#endif