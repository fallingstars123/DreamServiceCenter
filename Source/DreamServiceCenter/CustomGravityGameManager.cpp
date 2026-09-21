// Copyright (c) 2026. All rights reserved.

#include "CustomGravityGameManager.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogCustomGravityGameManager, Log, All);

ACustomGravityGameManager::ACustomGravityGameManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

ACharacter* ACustomGravityGameManager::ResolveTargetCharacter()
{
	if (IsValid(TargetCharacter))
	{
		return TargetCharacter;
	}

	TargetCharacter = UGameplayStatics::GetPlayerCharacter(this, PlayerIndex);
	return TargetCharacter;
}

UCustomGravityComponent* ACustomGravityGameManager::ResolveGravityComponent()
{
	ACharacter* Character = ResolveTargetCharacter();
	if (!IsValid(Character))
	{
		UE_LOG(
			LogCustomGravityGameManager,
			Warning,
			TEXT("Player character %d is not available."),
			PlayerIndex);
		return nullptr;
	}

	if (IsValid(CachedGravityComponent) && CachedGravityComponent->GetOwner() == Character)
	{
		return CachedGravityComponent;
	}

	CachedGravityComponent = Character->FindComponentByClass<UCustomGravityComponent>();
	if (!CachedGravityComponent && bAutoCreateComponentIfMissing)
	{
		CachedGravityComponent = NewObject<UCustomGravityComponent>(
			Character,
			TEXT("RuntimeCustomGravityComponent"));

		if (CachedGravityComponent)
		{
			Character->AddInstanceComponent(CachedGravityComponent);
			CachedGravityComponent->RegisterComponent();
		}
	}

	if (!CachedGravityComponent)
	{
		UE_LOG(
			LogCustomGravityGameManager,
			Warning,
			TEXT("%s has no CustomGravityComponent."),
			*GetNameSafe(Character));
	}

	return CachedGravityComponent;
}

bool ACustomGravityGameManager::SetPlayerGravityDirection(
	FVector NewGravityDirection)
{
	UCustomGravityComponent* Component = ResolveGravityComponent();
	if (!Component || NewGravityDirection.IsNearlyZero())
	{
		return false;
	}

	Component->SetGravityDirection(NewGravityDirection);
	return true;
}

bool ACustomGravityGameManager::SetPlayerGravityScale(float NewGravityScale)
{
	UCustomGravityComponent* Component = ResolveGravityComponent();
	if (!Component || !FMath::IsFinite(NewGravityScale))
	{
		return false;
	}

	Component->SetGravityScale(NewGravityScale);
	return true;
}

bool ACustomGravityGameManager::SetPlayerMaxGravityFallSpeed(
	float NewMaxGravityFallSpeed)
{
	UCustomGravityComponent* Component = ResolveGravityComponent();
	if (!Component || !FMath::IsFinite(NewMaxGravityFallSpeed))
	{
		return false;
	}

	Component->SetMaxGravityFallSpeed(NewMaxGravityFallSpeed);
	return true;
}

bool ACustomGravityGameManager::SetPlayerGravityPreset(
	ECustomGravityPreset Preset)
{
	UCustomGravityComponent* Component = ResolveGravityComponent();
	if (!Component)
	{
		return false;
	}

	Component->SetGravityPreset(Preset);
	return true;
}

bool ACustomGravityGameManager::SetPlayerGravityByNumber(int32 GravityNumber)
{
	UCustomGravityComponent* Component = ResolveGravityComponent();
	return Component && Component->SetGravityByNumber(GravityNumber);
}

bool ACustomGravityGameManager::TogglePlayerGravityAxisByNumber(int32 AxisNumber)
{
	switch (AxisNumber)
	{
	case 1:
		return TogglePlayerGravityX();
	case 2:
		return TogglePlayerGravityY();
	case 3:
		return TogglePlayerGravityZ();
	default:
		UE_LOG(
			LogCustomGravityGameManager,
			Warning,
			TEXT("TogglePlayerGravityAxisByNumber expects 1-3, received %d."),
			AxisNumber);
		return false;
	}
}

bool ACustomGravityGameManager::TogglePlayerGravityX()
{
	return TogglePlayerGravityOnAxis(FVector::XAxisVector);
}

bool ACustomGravityGameManager::TogglePlayerGravityY()
{
	return TogglePlayerGravityOnAxis(FVector::YAxisVector);
}

bool ACustomGravityGameManager::TogglePlayerGravityZ()
{
	return TogglePlayerGravityOnAxis(FVector::ZAxisVector);
}

bool ACustomGravityGameManager::TogglePlayerGravityOnAxis(
	const FVector& PositiveAxis)
{
	UCustomGravityComponent* Component = ResolveGravityComponent();
	if (!Component)
	{
		return false;
	}

	const FVector Axis = PositiveAxis.GetSafeNormal();
	const FVector CurrentDirection =
		Component->GetGravityDirection().GetSafeNormal();
	const float AxisDot = FVector::DotProduct(CurrentDirection, Axis);

	// If gravity is already on this axis, reverse it. Otherwise start on the
	// negative side so every axis has deterministic first-press behaviour.
	const FVector NewDirection = FMath::Abs(AxisDot) > 0.999f
		? (AxisDot > 0.0f ? -Axis : Axis)
		: -Axis;

	Component->SetGravityDirection(NewDirection);
	return true;
}

bool ACustomGravityGameManager::Gravity1()
{
	return SetPlayerGravityByNumber(1);
}

bool ACustomGravityGameManager::Gravity2()
{
	return SetPlayerGravityByNumber(2);
}

bool ACustomGravityGameManager::Gravity3()
{
	return SetPlayerGravityByNumber(3);
}

bool ACustomGravityGameManager::Gravity4()
{
	return SetPlayerGravityByNumber(4);
}

bool ACustomGravityGameManager::Gravity5()
{
	return SetPlayerGravityByNumber(5);
}

bool ACustomGravityGameManager::Gravity6()
{
	return SetPlayerGravityByNumber(6);
}

FVector ACustomGravityGameManager::GetPlayerGravityDirection() const
{
	return IsValid(CachedGravityComponent)
		? CachedGravityComponent->GetGravityDirection()
		: FVector::DownVector;
}
