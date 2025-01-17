// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#define COLLISION_PLAYER ECollisionChannel::ECC_GameTraceChannel1
#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel2

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set collision capsule
	GetCapsuleComponent()->BodyInstance.SetCollisionProfileName("Enemy");
	GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);
	GetCapsuleComponent()->SetCollisionObjectType(COLLISION_ENEMY);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_ENEMY, ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_PLAYER, ECollisionResponse::ECR_Overlap);

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.1f;

	Health = 1;
	MaxHealth = 1;

	bCanRotate = true;
	bCanBeDamaged = true;

	// Configure Overlapping
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::UpdateHealth(int Value)
{
	if (Health + Value > MaxHealth)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy: Health is Max(%d) - %d"), GetMaxHealth(), GetHealth());
	}
	else if (Health + Value < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy has no health - %d"), GetHealth());
	}
	else
	{
		Health += Value;
		UE_LOG(LogTemp, Warning, TEXT("Enemy: Health = %d"), GetHealth());
	}
}

int AEnemy::GetHealth()
{
	return Health;
}

int AEnemy::GetMaxHealth()
{
	return MaxHealth;
}

EEnemyType::EnemyType AEnemy::GetEnemyType()
{
	return EnemyType;
}

void AEnemy::SetCanRotate(bool CanRotate)
{
	if (bCanRotate)
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
		GetCharacterMovement()->bConstrainToPlane = true;
		GetCharacterMovement()->bSnapToPlaneAtStart = true;
		GetCharacterMovement()->bIgnoreBaseRotation = false;
	}
	else
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 0.f);
		GetCharacterMovement()->bConstrainToPlane = true;
		GetCharacterMovement()->bSnapToPlaneAtStart = true;
		GetCharacterMovement()->bIgnoreBaseRotation = true;
	}
}

bool AEnemy::GetCanRotate()
{
	return bCanRotate;
}

float AEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Call the base class - this will tell us how much damage to apply  
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (bCanBeDamaged)
	{
		if (ActualDamage > 0.f)
		{
			UpdateHealth(-FMath::FloorToInt(ActualDamage));
			UE_LOG(LogTemp, Warning, TEXT("DAMAGE: %d"), FMath::FloorToInt(ActualDamage));

			bCanBeDamaged = false;

			// If the damage depletes our health set our lifespan to zero - which will destroy the actor  
			if (Health <= 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Health == 0"));
				//ClearComponentOverlaps();
				//SetLifeSpan(0.001f);
			}
		}
	}

	return ActualDamage;
}

void AEnemy::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlaping"));

	if (OtherActor && (OtherActor != this) && OtherComp && OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
	{
		TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent DamageEvent(ValidDamageTypeClass);
		APlayerController* PlayerCtrl = Cast<APlayerController>(GetInstigatorController());
		OtherActor->TakeDamage(1, DamageEvent, PlayerCtrl, this);
	}
}

void AEnemy::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ClearComponentOverlaps();

	UE_LOG(LogTemp, Warning, TEXT("Stopped Overlaping"));
}

TArray<ATargetPoint*> AEnemy::GetWaypoints()
{
	return Waypoints;
}

#if WITH_EDITOR
void AEnemy::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AEnemy, bCanRotate))
	{
		SetCanRotate(bCanRotate);
	}
	Super::PostEditChangeProperty(e);
}
#endif