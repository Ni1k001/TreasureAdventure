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
	CollisionComp->SetHiddenInGame(false);

	Speed = 1;
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
		Mesh->SetRelativeLocation(FMath::Lerp(StartPosition, EndPosition, Delta));
}

void ASpecialBlock::TimelineFinishedCallback()
{
	UE_LOG(LogTemp, Warning, TEXT("Finish\t%f , %f , %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	if (GetActorLocation() == EndPosition)
	{
		Swap(StartPosition, EndPosition);
		Timeline.SetPlaybackPosition(0.f, false);
	}
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