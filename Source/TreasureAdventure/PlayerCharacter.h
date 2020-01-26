// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "TreasureAdventure.h"
#include "Components/TimelineComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

/*UENUM(BlueprintType)
enum class EInputMode : uint8
{
	ENone 				UMETA(DisplayName = "None"),
	EGameAndUIMode 		UMETA(DisplayName = "GameAndUIMode"),
	EGameOnlyMode 		UMETA(DisplayName = "GameOnlyMode"),
	EUIOnlyMode 		UMETA(DisplayName = "UIOnlyMode")
};*/

UENUM(BlueprintType)
enum class EInputMode : uint8
{
	EGame 		UMETA(DisplayName = "GameMode"),
	ECursor			UMETA(DisplayName = "CursorMode"),
};

//#####################################
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCursorPressDelegate, bool, Delta);
//#####################################

UCLASS()
class TREASUREADVENTURE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

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

	UFUNCTION(BlueprintCallable, Category="Player|Health")
		void UpdateHealth(int InHealth);

	UFUNCTION(BlueprintGetter, Category = "Player|Health")
		int GetHealth();

	UFUNCTION(BlueprintGetter, Category = "Player|Health")
		int GetMaxHealth();

	UFUNCTION(Category = "Player|Collectable")
		void UpdateCoinCount();

	UFUNCTION(BlueprintGetter, Category = "Player|Collectable")
		int GetCoinCount();

private:
	UPROPERTY(EditAnywhere, BlueprintGetter = GetHealth, Category = "Player|Health")
		int Health;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetMaxHealth, Category = "Player|Health")
		int MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Player|Health")
		float InvulnerableTime;

	UPROPERTY(EditAnywhere, Category = "Player|Health")
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
	UPROPERTY(EditAnywhere, BlueprintGetter = GetStarCoinCount, BlueprintSetter = SetStarCoinCount, Category = "Player|Collectable")
		int StarCoinCount = 0;

public:
	UFUNCTION(BlueprintGetter, Category = "Player|Collectable")
		int GetStarCoinCount();

	UFUNCTION(BlueprintCallable, Category = "Player|Collectable")
		void AddStarCoin();

	UFUNCTION(BlueprintSetter, Category = "Player|Collectable")
		void SetStarCoinCount(int InStarCoinCount);

private:
	UPROPERTY(BlueprintGetter = GetbIsInWater, BlueprintSetter = SetbIsInWater, Category = "Player|Air")
		bool bIsInWater;

	UPROPERTY(BlueprintGetter = GetAirAmount, BlueprintSetter = SetAirAmount, meta = (ClampMin = "0", ClampMax = "100", UIMin = "0", UIMax = "100"), Category = "Player|Air")
		float Air;

public:
	UFUNCTION(BlueprintSetter, Category = "Player|Air")
		void SetbIsInWater(bool InBIsInWater);

	UFUNCTION(BlueprintGetter, Category = "Player|Air")
		bool GetbIsInWater();

	UFUNCTION(BlueprintSetter, Category = "Player|Air")
		void SetAirAmount(float InAir);

	UFUNCTION(BlueprintGetter, Category = "Player|Air")
		float GetAirAmount();

private:
	UPROPERTY()
		EInputMode InputMode;

public:
	UFUNCTION()
		void ToggleInputMode();

	UFUNCTION()
		void OnCursorPressed();

	UPROPERTY(BlueprintAssignable)
		FCursorPressDelegate OnCursorPress;

	UFUNCTION()
		void OnCursorReleased();

	//##########################
	/*UFUNCTION(BlueprintPure, Category = "Runtime Inspector")
		EInputMode GetCurrentViewMode(const APlayerController* PlayerController);

	UFUNCTION()
		void ToggleInputMode();*/

	const FString EnumToString(const TCHAR* Enum, int32 EnumValue)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, Enum, true);
		if (!EnumPtr)
			return NSLOCTEXT("Invalid", "Invalid", "Invalid").ToString();

		#if WITH_EDITOR
			return EnumPtr->GetDisplayNameText(EnumValue).ToString();
		#else
			return EnumPtr->GetEnumName(EnumValue);
		#endif
	}

	//########################## MultiThreading test
public:
	UPROPERTY(EditAnywhere, Category = MultiThreading)
		int32 MaxPrime;

	UFUNCTION(BlueprintCallable, Category = "Runtime Inspector|MultiThreading")
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