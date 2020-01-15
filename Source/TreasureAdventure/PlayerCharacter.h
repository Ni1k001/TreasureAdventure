// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "TreasureAdventure.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"

#include "PlayerCharacter.generated.h"


UCLASS()
class TREASUREADVENTURE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void UpdateHealth(int Value);

	UFUNCTION(BlueprintCallable)
		int GetHealth();
	
	UFUNCTION(BlueprintCallable)
		int GetMaxHealth();

	UFUNCTION()
		void UpdateCoinCount();

	UFUNCTION(BlueprintCallable)
		int GetCoinCount();

private:
	UPROPERTY(EditAnywhere, Category = "Health")
		int Health;

	UPROPERTY(EditAnywhere, Category = "Health")
		int MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Health")
		float InvulnerableTime;

	UPROPERTY(EditAnywhere, Category = "Health")
		float BlinkingTime;;

	FTimerHandle DamageTimer;

	FTimerHandle BlinkingTimer;

	void AllowDamage();

	void Blink();

protected:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		class USoundBase* LifeUpSound;

private:
	UPROPERTY(EditAnywhere, Category = "Config")
		int StarCoinCount = 0;

public:
	UFUNCTION(BlueprintPure)
		int GetStarCoinCount();

	UFUNCTION(BlueprintCallable)
		void AddStarCoin();

	UFUNCTION(BlueprintCallable)
		void SetStarCoinCount(int value);

	
	//########################## MultiThreading test
public:
	UPROPERTY(EditAnywhere, Category = MultiThreading)
		int32 MaxPrime;

	UFUNCTION(BlueprintCallable, Category = MultiThreading)
		void CalculatePrimeNumbersAsync();
};

namespace ThreadingTest
{
	static void CalculatePrimeNumbers(int32 UpperLimit)
	{
		for (int32 i = 1; i <= UpperLimit; i++)
		{
			bool isPrime = true;

			for (int32 j = 2; j <= i / 2; j++)
			{
				if (FMath::Fmod(i, j) == 0)
				{
					isPrime = false;
					break;
				}
			}

			if (isPrime)
			{
				GLog->Log("Prime number #" + FString::FromInt(i) + ": " + FString::FromInt(i));
			}
		}
	}
}

class PrimeCalculationAsyncTask : public FNonAbandonableTask
{
	int32 MaxPrime;

public:
	PrimeCalculationAsyncTask(int32 MaxPrime)
	{
		this->MaxPrime = MaxPrime;
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(PrimeCalculationAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	void DoWork()
	{
		ThreadingTest::CalculatePrimeNumbers(MaxPrime);

		UE_LOG(LogTemp, Warning, TEXT("##############################################"));
		UE_LOG(LogTemp, Warning, TEXT("FINISH"));
		UE_LOG(LogTemp, Warning, TEXT("##############################################"));
	}
};