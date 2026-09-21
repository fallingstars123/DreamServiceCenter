// Copyright (c) 2026. All rights reserved.

#include "CustomGravityComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY_STATIC(LogCustomGravityComponent, Log, All);

namespace CustomGravity
{
	constexpr float DirectionTolerance = 1.e-4f;
	constexpr float MaxGravityScale = 20.0f;

	FVector NormalizeOrDefault(const FVector& Direction)
	{
		return Direction.IsNearlyZero()
			? FVector::DownVector
			: Direction.GetSafeNormal();
	}
}

UCustomGravityComponent::UCustomGravityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;
	SetIsReplicatedByDefault(true);
}

void UCustomGravityComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!ResolveCharacterAndMovement())
	{
		UE_LOG(
			LogCustomGravityComponent,
			Error,
			TEXT("%s must be attached to an ACharacter with a CharacterMovementComponent."),
			*GetNameSafe(this));
		SetComponentTickEnabled(false);
		return;
	}

	// Gravity and capsule alignment must be ready before CharacterMovement simulates.
	CharacterMovement->AddTickPrerequisiteComponent(this);

	if (bApplyInitialGravityOnBeginPlay && GetOwner()->HasAuthority())
	{
		CurrentGravityDirection = CustomGravity::NormalizeOrDefault(InitialGravityDirection);
	}

	CharacterMovement->GravityScale = FMath::Clamp(GravityScale, 0.0f, CustomGravity::MaxGravityScale);
	ApplyGravityDirection(CurrentGravityDirection, false);
	AlignCharacter(0.0f, true);
}

void UCustomGravityComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CharacterMovement)
	{
		CharacterMovement->RemoveTickPrerequisiteComponent(this);
	}

	Super::EndPlay(EndPlayReason);
}

void UCustomGravityComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!ResolveCharacterAndMovement())
	{
		return;
	}

	AlignCharacter(DeltaTime, false);
	ClampGravityFallSpeed();
}

void UCustomGravityComponent::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCustomGravityComponent, CurrentGravityDirection);
	DOREPLIFETIME(UCustomGravityComponent, GravityScale);
}

bool UCustomGravityComponent::ResolveCharacterAndMovement()
{
	if (!CharacterOwner)
	{
		CharacterOwner = Cast<ACharacter>(GetOwner());
	}

	if (CharacterOwner && !CharacterMovement)
	{
		CharacterMovement = CharacterOwner->GetCharacterMovement();
	}

	return CharacterOwner != nullptr && CharacterMovement != nullptr;
}

void UCustomGravityComponent::SetGravityDirection(FVector NewGravityDirection)
{
	if (!ResolveCharacterAndMovement())
	{
		return;
	}

	if (NewGravityDirection.IsNearlyZero())
	{
		UE_LOG(
			LogCustomGravityComponent,
			Warning,
			TEXT("SetGravityDirection ignored a zero vector on %s."),
			*GetNameSafe(GetOwner()));
		return;
	}

	const FVector NormalizedDirection = NewGravityDirection.GetSafeNormal();
	ApplyGravityDirection(NormalizedDirection, true);

	if (!GetOwner()->HasAuthority())
	{
		ServerSetGravityDirection(NormalizedDirection);
	}
	else
	{
		GetOwner()->ForceNetUpdate();
	}
}

void UCustomGravityComponent::SetGravityScale(float NewGravityScale)
{
	if (!ResolveCharacterAndMovement() || !FMath::IsFinite(NewGravityScale))
	{
		return;
	}

	GravityScale = FMath::Clamp(NewGravityScale, 0.0f, CustomGravity::MaxGravityScale);
	CharacterMovement->GravityScale = GravityScale;

	if (!GetOwner()->HasAuthority())
	{
		ServerSetGravityScale(GravityScale);
	}
	else
	{
		GetOwner()->ForceNetUpdate();
	}
}

void UCustomGravityComponent::SetMaxGravityFallSpeed(
	float NewMaxGravityFallSpeed)
{
	if (!FMath::IsFinite(NewMaxGravityFallSpeed))
	{
		return;
	}

	MaxGravityFallSpeed = FMath::Max(0.0f, NewMaxGravityFallSpeed);
	ClampGravityFallSpeed();
}

void UCustomGravityComponent::SetGravityPreset(ECustomGravityPreset Preset)
{
	SetGravityDirection(GetDirectionForPreset(Preset));
}

bool UCustomGravityComponent::SetGravityByNumber(int32 GravityNumber)
{
	if (GravityNumber < 1 || GravityNumber > 6)
	{
		UE_LOG(
			LogCustomGravityComponent,
			Warning,
			TEXT("SetGravityByNumber expects 1-6, received %d."),
			GravityNumber);
		return false;
	}

	SetGravityPreset(static_cast<ECustomGravityPreset>(GravityNumber - 1));
	return true;
}

void UCustomGravityComponent::Gravity1()
{
	SetGravityByNumber(1);
}

void UCustomGravityComponent::Gravity2()
{
	SetGravityByNumber(2);
}

void UCustomGravityComponent::Gravity3()
{
	SetGravityByNumber(3);
}

void UCustomGravityComponent::Gravity4()
{
	SetGravityByNumber(4);
}

void UCustomGravityComponent::Gravity5()
{
	SetGravityByNumber(5);
}

void UCustomGravityComponent::Gravity6()
{
	SetGravityByNumber(6);
}

FVector UCustomGravityComponent::GetGravityDirection() const
{
	return CharacterMovement
		? CharacterMovement->GetGravityDirection()
		: CustomGravity::NormalizeOrDefault(CurrentGravityDirection);
}

FVector UCustomGravityComponent::GetDirectionForPreset(ECustomGravityPreset Preset)
{
	switch (Preset)
	{
	case ECustomGravityPreset::WorldNegativeZ:
		return FVector(0.0, 0.0, -1.0);
	case ECustomGravityPreset::WorldPositiveZ:
		return FVector(0.0, 0.0, 1.0);
	case ECustomGravityPreset::WorldPositiveX:
		return FVector(1.0, 0.0, 0.0);
	case ECustomGravityPreset::WorldNegativeX:
		return FVector(-1.0, 0.0, 0.0);
	case ECustomGravityPreset::WorldPositiveY:
		return FVector(0.0, 1.0, 0.0);
	case ECustomGravityPreset::WorldNegativeY:
		return FVector(0.0, -1.0, 0.0);
	default:
		return FVector::DownVector;
	}
}

void UCustomGravityComponent::ApplyGravityDirection(
	const FVector& NewGravityDirection,
	bool bBroadcastChange)
{
	if (!ResolveCharacterAndMovement())
	{
		return;
	}

	const FVector NormalizedDirection = CustomGravity::NormalizeOrDefault(NewGravityDirection);
	const FVector PreviousDirection = CharacterMovement->GetGravityDirection().GetSafeNormal();
	const bool bDirectionChanged = !PreviousDirection.Equals(
		NormalizedDirection,
		CustomGravity::DirectionTolerance);

	CurrentGravityDirection = NormalizedDirection;
	CharacterMovement->SetGravityDirection(NormalizedDirection);

	if (!bDirectionChanged)
	{
		return;
	}

	if (bForceFallingOnGravityChange && CharacterMovement->IsMovingOnGround())
	{
		CharacterOwner->SetBase(static_cast<FMovementBaseInterfaceData*>(nullptr));
		CharacterMovement->SetMovementMode(MOVE_Falling);
	}

	if (bRotateControllerOnGravityChange)
	{
		RotateController(PreviousDirection, NormalizedDirection);
	}

	if (bAlignCharacterToGravity && AlignmentSpeed <= 0.0f)
	{
		AlignCharacter(0.0f, true);
	}

	if (bBroadcastChange)
	{
		OnGravityChanged.Broadcast(NormalizedDirection);
	}
}

void UCustomGravityComponent::AlignCharacter(float DeltaTime, bool bInstant)
{
	if (!bAlignCharacterToGravity || !CharacterOwner)
	{
		return;
	}

	const FVector DesiredUp = -CustomGravity::NormalizeOrDefault(CurrentGravityDirection);
	const FVector CurrentUp = CharacterOwner->GetActorUpVector().GetSafeNormal();
	if (CurrentUp.Equals(DesiredUp, CustomGravity::DirectionTolerance))
	{
		return;
	}

	const FQuat CurrentRotation = CharacterOwner->GetActorQuat();
	const FQuat UpAlignment = FQuat::FindBetweenNormals(CurrentUp, DesiredUp);
	const FQuat TargetRotation = (UpAlignment * CurrentRotation).GetNormalized();

	FQuat NewRotation = TargetRotation;
	if (!bInstant && AlignmentSpeed > 0.0f)
	{
		const float RemainingAngle = CurrentRotation.AngularDistance(TargetRotation);
		const float MaxStep = FMath::DegreesToRadians(AlignmentSpeed) * DeltaTime;
		const float Alpha = RemainingAngle > UE_SMALL_NUMBER
			? FMath::Clamp(MaxStep / RemainingAngle, 0.0f, 1.0f)
			: 1.0f;
		NewRotation = FQuat::Slerp(CurrentRotation, TargetRotation, Alpha);
	}

	CharacterOwner->SetActorRotation(NewRotation, ETeleportType::None);
}

void UCustomGravityComponent::ClampGravityFallSpeed()
{
	if (!CharacterMovement || MaxGravityFallSpeed <= 0.0f)
	{
		return;
	}

	const FVector GravityDirection =
		CustomGravity::NormalizeOrDefault(CurrentGravityDirection);
	const float FallSpeed = FVector::DotProduct(
		CharacterMovement->Velocity,
		GravityDirection);

	if (FallSpeed > MaxGravityFallSpeed)
	{
		CharacterMovement->Velocity -= GravityDirection *
			(FallSpeed - MaxGravityFallSpeed);
	}
}

void UCustomGravityComponent::RotateController(
	const FVector& PreviousDirection,
	const FVector& NewDirection)
{
	APlayerController* PlayerController = CharacterOwner
		? Cast<APlayerController>(CharacterOwner->GetController())
		: nullptr;
	if (!PlayerController || PreviousDirection.IsNearlyZero() || NewDirection.IsNearlyZero())
	{
		return;
	}

	const FVector PreviousUp = -PreviousDirection.GetSafeNormal();
	const FVector NewUp = -NewDirection.GetSafeNormal();
	const FQuat GravityDelta = FQuat::FindBetweenNormals(PreviousUp, NewUp);
	const FQuat NewControlRotation = (
		GravityDelta * PlayerController->GetControlRotation().Quaternion()).GetNormalized();
	PlayerController->SetControlRotation(NewControlRotation.Rotator());
}

void UCustomGravityComponent::OnRep_GravityDirection()
{
	ApplyGravityDirection(CurrentGravityDirection, true);
}

void UCustomGravityComponent::OnRep_GravityScale()
{
	if (ResolveCharacterAndMovement())
	{
		GravityScale = FMath::Clamp(GravityScale, 0.0f, CustomGravity::MaxGravityScale);
		CharacterMovement->GravityScale = GravityScale;
	}
}

void UCustomGravityComponent::ServerSetGravityDirection_Implementation(
	FVector NewGravityDirection)
{
	SetGravityDirection(NewGravityDirection);
}

void UCustomGravityComponent::ServerSetGravityScale_Implementation(float NewGravityScale)
{
	SetGravityScale(NewGravityScale);
}
