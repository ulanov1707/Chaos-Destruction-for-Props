// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Field/FieldSystemComponent.h"
#include "Field/FieldSystemObjects.h"
#include "GameFramework/Actor.h"
#include "DamageActor.generated.h"

UCLASS()
class KILLCHAINDESTRUCTION_API ADamageActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UFieldSystemComponent* FieldSystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCullingField* StrainCulling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		URadialFalloff* CullingField;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		URadialFalloff* Strain;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		URadialVector* Force;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UUniformInteger* State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StrainMagnitude = 5000000.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float ForceMagnitude = 1500.0f;

protected:
	URadialFalloff* GetCullingField() const;

	UCullingField* GetWakeField() const;

	UCullingField* GetStrainField(const float StrainDamage) const;

	UCullingField* GetForceField(const float ForceMagnitude) const;

public:
	UFUNCTION(BlueprintCallable)
		void ApplyDamage(const float StrainDamage, const float ForceMagnitude) const;
};
