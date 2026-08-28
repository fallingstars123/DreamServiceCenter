// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GaussianSplatSelectionBoxComponent.generated.h"

UENUM(BlueprintType)
enum class EGaussianSplatSelectionBoxMode : uint8
{
	Cull UMETA(DisplayName = "Cull"),
	Keep UMETA(DisplayName = "Keep")
};

/**
 * An editor-visible box used to mask Gaussian splats. The component never
 * collides and is hidden during play; only its transform and extent are used.
 */
UCLASS(
	ClassGroup = (Rendering),
	EditInlineNew,
	DefaultToInstanced,
	HideCategories = (
		Object,
		"Gaussian Splatting",
		Transform,
		Shape,
		HLOD,
		Collision,
		Rendering,
		Mobile,
		Mobility,
		Physics,
		Navigation,
		LOD,
		Lighting,
		TextureStreaming,
		Activation,
		"Components|Activation",
		Cooking,
		Tags,
		AssetUserData,
		Replication,
		ComponentTick,
		Events,
		Input),
	meta = (BlueprintSpawnableComponent))
class NANOGS_API UGaussianSplatSelectionBoxComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UGaussianSplatSelectionBoxComponent(const FObjectInitializer& ObjectInitializer);

	/** User-facing label shown for this entry in the actor details panel. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection Box", meta = (DisplayName = "Name"))
	FName SelectionBoxName = NAME_None;

	/** Transform relative to the Gaussian Splat actor. Synchronized with the viewport box. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection Box", meta = (DisplayName = "Transform"))
	FTransform SelectionBoxTransform = FTransform::Identity;

	/** Internal mode controlled by the owning Gaussian Splat actor. */
	UPROPERTY()
	EGaussianSplatSelectionBoxMode SelectionMode = EGaussianSplatSelectionBoxMode::Cull;

	void SetSelectionMode(EGaussianSplatSelectionBoxMode NewMode);

protected:
	virtual void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport) override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	void NotifyOwnerSelectionChanged() const;
	bool bSynchronizingTransform = false;
};
