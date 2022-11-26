// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Particles/ParticleSystem.h"
#include "Destructible.generated.h"

class ADamageActor;


USTRUCT(BlueprintType)
struct FProjectileConfig
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageRadius = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StrainAmount = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ForceAmount = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* ImpactFX;
};

UCLASS(Abstract)
class KILLCHAINDESTRUCTION_API ADestructible : public AActor
{
	GENERATED_BODY()

public:
	ADestructible();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UGeometryCollectionComponent* Destructible;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Config", meta = (Categories = "Material"))
		FGameplayTag Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Config", meta = (Categories = "Projectile"))
		TMap<FGameplayTag, FProjectileConfig> ProjectileConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Config", meta = (Categories = "Material"))
		TMap<FGameplayTag, float> MaterialDamageConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Config")
		bool bUseDamageOverride = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Config")
		float DamageOverride = 5000000;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnDestructionEventReceived(const FVector& Location, const FGameplayTag& Projectile);

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
};
