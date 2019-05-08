// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "TAGameInstance.h"
#include "TreasureAdventureGameMode.h"
#include "Engine/Blueprint.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#define COLLISION_PLAYER ECollisionChannel::ECC_GameTraceChannel1

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set collision capsule
	GetCapsuleComponent()->BodyInstance.SetCollisionProfileName("Player");
	GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);
	GetCapsuleComponent()->SetCollisionObjectType(COLLISION_PLAYER);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_PLAYER, ECollisionResponse::ECR_Block);

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.1f;

	Health = 1;
	MaxHealth = 2;

	InvulnerableTime = 1.f;

	bCanBeDamaged = true;


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Turn" and "LookUp" handles devices that provide an absolute delta, such as a mouse.
	// "TurnRate" and "LookUpRate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);

	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

	// Set up action key bindings
	//PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APlayerCharacter::PauseGame);
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::UpdateHealth(int Value)
{
	if (Health + Value > MaxHealth)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health is Max(%d) - %d"), GetMaxHealth(), GetHealth());
	}
	else if (Health + Value < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player has no health - %d"), GetHealth());
	}
	else
	{
		Health += Value;
		UE_LOG(LogTemp, Warning, TEXT("Health = %d"), GetHealth());
	}

	if (Health == 2)
		SetActorRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
	else if (Health == 1)
	{
		SetActorRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));
	}
}

int APlayerCharacter::GetHealth()
{
	return Health;
}

int APlayerCharacter::GetMaxHealth()
{
	return MaxHealth;
}

void APlayerCharacter::UpdateCoinCount()
{
	UTAGameInstance* GI = Cast<UTAGameInstance>(GetGameInstance());

	if (GI)
	{

		GI->UpdateCoinCount();
	}

	if (GetCoinCount() == 0)
	{
		if (LifeUpSound)
		{
			UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(this, LifeUpSound);
			AudioComponent->Play();
		}
	}
}

int APlayerCharacter::GetCoinCount()
{
	UTAGameInstance* GI = Cast<UTAGameInstance>(GetGameInstance());
	if (GI)
	{
		UE_LOG(LogTemp, Warning, TEXT("CURRENT COINS: %d"), GI->GetCurrentCoinCount());
		UE_LOG(LogTemp, Warning, TEXT("TOTAL COINS: %d"), GI->GetTotalCoinCount());
		return GI->GetCurrentCoinCount();
	}

	return 0;
}

void APlayerCharacter::AllowDamage()
{
	UE_LOG(LogTemp, Warning, TEXT("DAMAGE ALLOWED"));
	bCanBeDamaged = true;
}

float APlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
			GetWorldTimerManager().SetTimer(DamageTimer, this, &APlayerCharacter::AllowDamage, 1.f, false, InvulnerableTime);

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