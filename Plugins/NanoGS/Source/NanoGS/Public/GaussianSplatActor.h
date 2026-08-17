// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GaussianSplatSelectionBoxComponent.h"
#include "GaussianSplatActor.generated.h"

class UGaussianSplatComponent;

/**
 * Simple actor for placing Gaussian Splats in the level.
 * Drag and drop a Gaussian Splat Asset from the Content Browser to spawn this actor.
 */
UCLASS(NotPlaceable)
class NANOGS_API AGaussianSplatActor : public AActor
{
	GENERATED_BODY()

public:
	AGaussianSplatActor();

	//~ Begin UObject Interface
	virtual void PostLoad() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditUndo() override;
#endif
	//~ End UObject Interface

	/** The Gaussian Splat component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gaussian Splatting")
	TObjectPtr<UGaussianSplatComponent> GaussianSplatComponent;

	/** Enable all cull boxes. Splats inside any cull box are hidden. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gaussian Splatting|Selection Boxes", meta = (DisplayName = "启用剔除选区"))
	bool bEnableCullSelectionBoxes = false;

	/** Enable all keep boxes. Their union is retained and wins over overlapping cull boxes. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gaussian Splatting|Selection Boxes", meta = (DisplayName = "启用保留选区"))
	bool bEnableKeepSelectionBoxes = false;

	/** Recreate render data after a selection box is moved, resized, added, or removed. */
	void NotifySelectionBoxesChanged();

	const TArray<TObjectPtr<UGaussianSplatSelectionBoxComponent>>& GetCullSelectionBoxes() const { return CullSelectionBoxes; }
	const TArray<TObjectPtr<UGaussianSplatSelectionBoxComponent>>& GetKeepSelectionBoxes() const { return KeepSelectionBoxes; }

	static constexpr int32 MaxSelectionBoxesPerMode = 16;

private:
	UPROPERTY(EditInstanceOnly, Instanced, Category = "Gaussian Splatting|Selection Boxes",
		meta = (DisplayName = "剔除选区列表", TitleProperty = "SelectionBoxName", NoElementDuplicate))
	TArray<TObjectPtr<UGaussianSplatSelectionBoxComponent>> CullSelectionBoxes;

	UPROPERTY(EditInstanceOnly, Instanced, Category = "Gaussian Splatting|Selection Boxes",
		meta = (DisplayName = "保留选区列表", TitleProperty = "SelectionBoxName", NoElementDuplicate))
	TArray<TObjectPtr<UGaussianSplatSelectionBoxComponent>> KeepSelectionBoxes;

	UGaussianSplatSelectionBoxComponent* CreateSelectionBox(EGaussianSplatSelectionBoxMode Mode, int32 Index);
	void SynchronizeSelectionBoxes();
	void RemoveInvalidSelectionBoxes();
};
