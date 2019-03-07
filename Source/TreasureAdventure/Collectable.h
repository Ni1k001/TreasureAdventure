// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

UENUM(BlueprintType)
namespace ECollectable
{
	enum CollectableType
	{
		ECoin			UMETA(DisplayName = "Coin"),
		EStar			UMETA(DisplayName = "Star"),
	};
}

UCLASS()
class TREASUREADVENTURE_API ACollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		TEnumAsByte<ECollectable::CollectableType> CollectableType;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	UPROPERTY(EditAnywhere)
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config, meta = (ClampMin = "0", ClampMax = "7", UIMin = "0", UIMax = "7"))
		int StarID;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

#if WITH_EDITOR
	virtual bool CanEditChange(const UProperty* InProperty) const override;
#endif
};