// Fill out your copyright notice in the Description page of Project Settings.

#include "Destructible.h"

#include "DamageActor.h"

ADestructible::ADestructible()
{
	PrimaryActorTick.bCanEverTick = false;

	Destructible = CreateDefaultSubobject<UGeometryCollectionComponent>("Destructible");
	SetRootComponent(Destructible);
}

void ADestructible::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (bUseDamageOverride)
	{
		Destructible->DamageThreshold.Empty();
		Destructible->DamageThreshold.Add(DamageOverride);
	}
	else if (const float* Damage = MaterialDamageConfig.Find(Material))
	{
		// TODO: use smaller numbers for damage and add to the base material damage amount
		Destructible->DamageThreshold.Empty();
		Destructible->DamageThreshold.Add(*Damage);
	}
}

void ADestructible::OnDestructionEventReceived_Implementation(const FVector& Location, const FGameplayTag& Projectile)
{
	const FProjectileConfig& Data = ProjectileConfig.FindRef(Projectile);
	const FTransform Transform(FRotator::ZeroRotator, Location, FVector(Data.DamageRadius));

	// TODO: use a damage pool
	ADamageActor* Damage = GetWorld()->SpawnActor<ADamageActor>(ADamageActor::StaticClass(), Transform);
	Damage->ApplyDamage(Data.StrainAmount, Data.ForceAmount);

	Damage->Destroy();
}