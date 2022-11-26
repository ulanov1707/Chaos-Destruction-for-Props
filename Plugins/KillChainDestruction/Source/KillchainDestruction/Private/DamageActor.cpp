// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageActor.h"

ADamageActor::ADamageActor()
{
	PrimaryActorTick.bCanEverTick = false;

	FieldSystemComponent = CreateDefaultSubobject<UFieldSystemComponent>("FieldSystem");
	SetRootComponent(FieldSystemComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetVisibility(true);
	SphereComponent->SetHiddenInGame(false);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	StrainCulling = CreateDefaultSubobject<UCullingField>("StrainCulling");
	CullingField = CreateDefaultSubobject<URadialFalloff>("CullingVolume");
	Strain = CreateDefaultSubobject<URadialFalloff>("Strain");
	Force = CreateDefaultSubobject<URadialVector>("Force");
	State = CreateDefaultSubobject<UUniformInteger>("State");
}

URadialFalloff* ADamageActor::GetCullingField() const
{
	URadialFalloff* Culling = CullingField->SetRadialFalloff(1.0f, 0.0f, 1.0f, 0.0f,
		SphereComponent->GetScaledSphereRadius(),
		SphereComponent->GetComponentLocation(),
		Field_FallOff_None);

	return Culling;
}

UCullingField* ADamageActor::GetWakeField() const
{
	Chaos::EObjectStateType StateType = Chaos::EObjectStateType::Dynamic;
	State->SetUniformInteger(static_cast<int32>(StateType));

	return StrainCulling->SetCullingField(GetCullingField(), State, Field_Culling_Outside);
}

UCullingField* ADamageActor::GetStrainField(const float StrainDamage) const
{
	Strain->SetRadialFalloff(StrainDamage, 0.0f, 1.0f, 0.0f,
		SphereComponent->GetScaledSphereRadius(),
		SphereComponent->GetComponentLocation(),
		Field_FallOff_None);

	return StrainCulling->SetCullingField(GetCullingField(), Strain, Field_Culling_Outside);
}

UCullingField* ADamageActor::GetForceField(const float ForceMagnitude) const
{
	Force->SetRadialVector(ForceMagnitude, SphereComponent->GetComponentLocation());

	return StrainCulling->SetCullingField(GetCullingField(), Force, Field_Culling_Outside);
}

void ADamageActor::ApplyDamage(const float StrainDamage, const float ForceMagnitude) const
{
	//FieldSystemComponent->ApplyPhysicsField(true, Field_DynamicState,
	//	nullptr, GetWakeField());

	FieldSystemComponent->ApplyPhysicsField(true, Field_ExternalClusterStrain,
		nullptr, GetStrainField(StrainDamage));

	FieldSystemComponent->ApplyPhysicsField(true, Field_LinearVelocity,
		nullptr, GetForceField(ForceMagnitude));
}