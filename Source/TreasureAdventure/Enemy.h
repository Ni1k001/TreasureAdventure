// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Enemy.generated.h"

UENUM(BlueprintType)
namespace EEnemyType
{
	enum EnemyType
	{
		EPatrol			UMETA(DisplayName = "Patrol"),
		ERush			UMETA(DisplayName = "Rush"),
	};
}

UCLASS()
class TREASUREADVENTURE_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> Waypoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void UpdateHealth(int Value);

	UFUNCTION(BlueprintCallable)
		int GetHealth();

	UFUNCTION(BlueprintCallable)
		int GetMaxHealth();

	UFUNCTION(BlueprintCallable)
		EEnemyType::EnemyType GetEnemyType();

	UFUNCTION(BlueprintPure, Category = "AI")
		TArray<ATargetPoint*> GetWaypoints();

protected:

	UFUNCTION()
		void SetCanRotate(bool CanRotate);

	UFUNCTION()
		bool GetCanRotate();

private:
	UPROPERTY(EditAnywhere, Category = "Health")
		int Health;

	UPROPERTY(EditAnywhere, Category = "Health")
		int MaxHealth;

	UPROPERTY(EditAnywhere, Category = Config)
		TEnumAsByte<EEnemyType::EnemyType> EnemyType;

	UPROPERTY(EditAnywhere, Category = Config)
		bool bCanRotate;

protected:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e);
#endif
};