// Copyright Epic Games, Inc. All Rights Reserved.

#include "GaussianSplatSelectionBoxComponent.h"
#include "GaussianSplatActor.h"

UGaussianSplatSelectionBoxComponent::UGaussianSplatSelectionBoxComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetGenerateOverlapEvents(false);
	SetCanEverAffectNavigation(false);
	SetHiddenInGame(true);
	bDrawOnlyIfSelected = false;
	ShapeColor = FColor(220, 55, 55);
}

void UGaussianSplatSelectionBoxComponent::SetSelectionMode(EGaussianSplatSelectionBoxMode NewMode)
{
	SelectionMode = NewMode;
	ShapeColor = SelectionMode == EGaussianSplatSelectionBoxMode::Keep
		? FColor(40, 220, 80)
		: FColor(220, 55, 55);
	MarkRenderStateDirty();
	NotifyOwnerSelectionChanged();
}

void UGaussianSplatSelectionBoxComponent::OnUpdateTransform(
	EUpdateTransformFlags UpdateTransformFlags,
	ETeleportType Teleport)
{
	Super::OnUpdateTransform(UpdateTransformFlags, Teleport);
	if (!bSynchronizingTransform)
	{
		SelectionBoxTransform = GetRelativeTransform();
	}
	NotifyOwnerSelectionChanged();
}

void UGaussianSplatSelectionBoxComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	NotifyOwnerSelectionChanged();
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

#if WITH_EDITOR
void UGaussianSplatSelectionBoxComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() ==
		GET_MEMBER_NAME_CHECKED(UGaussianSplatSelectionBoxComponent, SelectionBoxTransform))
	{
		TGuardValue<bool> SynchronizingGuard(bSynchronizingTransform, true);
		SetRelativeTransform(SelectionBoxTransform);
	}
	NotifyOwnerSelectionChanged();
}
#endif

void UGaussianSplatSelectionBoxComponent::NotifyOwnerSelectionChanged() const
{
	if (HasAnyFlags(RF_ClassDefaultObject) || !GetOwner())
	{
		return;
	}

	if (AGaussianSplatActor* SplatActor = Cast<AGaussianSplatActor>(GetOwner()))
	{
		SplatActor->NotifySelectionBoxesChanged();
	}
}
