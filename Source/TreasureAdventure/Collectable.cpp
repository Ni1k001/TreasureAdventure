// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectable.h"
#include "Engine.h"
#include "TreasureAdventure.h"
#include "PlayerCharacter.h"
#include "TAGameInstance.h"

// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(false);
	//Mesh->SetupAttachment(RootComponent);

	RootComponent = Mesh;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComp->SetSphereRadius(30.f);
	CollisionComp->SetupAttachment(RootComponent);
	CollisionComp->SetHiddenInGame(false);

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACollectable::BeginOverlap);

	StarID = 0;
	bHasRequirements = false;
	RequiredCoins = 0;

	RotationRate = FRotator(0.f, 0.f, 0.f);
}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Mesh->AddRelativeRotation(RotationRate);
}

void ACollectable::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor != NULL && OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		UTAGameInstance* GI = Cast<UTAGameInstance>(GetGameInstance());

		if (CollectableType == ECollectable::ECoin)
			Player->UpdateCoinCount();
		else if (CollectableType == ECollectable::EStar)
			GI->UpdateStarCount(StarID);
		else if (CollectableType == ECollectable::EStarCoin)
			Player->AddStarCoin();

		if (CollectSound)
		{
			UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(this, CollectSound);
			AudioComponent->Play();
		}

		Destroy();
	}
}


#if WITH_EDITOR
bool ACollectable::CanEditChange(const UProperty* InProperty) const
{
	const bool ParentVal = Super::CanEditChange(InProperty);

	if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(ACollectable, StarID) || InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(ACollectable, bHasRequirements))
	{
		return CollectableType == ECollectable::EStar;
	}

	return ParentVal;
}

void ACollectable::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (CollectableType != ECollectable::EStar)
		bHasRequirements = false;

	if (!bHasRequirements)
		RequiredCoins = 0;
}
#endif