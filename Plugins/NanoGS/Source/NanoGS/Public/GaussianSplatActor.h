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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gaussian Splatting|Selection Boxes", meta = (DisplayName = "Enable Cull Selection Boxes"))
	bool bEnableCullSelectionBoxes = false;

	/** Enable all keep boxes. Their union is retained; cull boxes can remove points inside it. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gaussian Splatting|Selection Boxes", meta = (DisplayName = "Enable Keep Selection Boxes"))
	bool bEnableKeepSelectionBoxes = false;

	/** Choose which operation wins where cull and keep boxes overlap. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gaussian Splatting|Selection Boxes",
		meta = (DisplayName = "Overlap Priority", EditCondition = "bEnableCullSelectionBoxes && bEnableKeepSelectionBoxes"))
	EGaussianSplatSelectionBoxMode SelectionBoxOverlapPriority = EGaussianSplatSelectionBoxMode::Cull;

	/** Recreate render data after a selection box is moved, resized, added, or removed. */
	void NotifySelectionBoxesChanged();

	const TArray<TObjectPtr<UGaussianSplatSelectionBoxComponent>>& GetCullSelectionBoxes() const { return CullSelectionBoxes; }
	const TArray<TObjectPtr<UGaussianSplatSelectionBoxComponent>>& GetKeepSelectionBoxes() const { return KeepSelectionBoxes; }

	static constexpr int32 MaxSelectionBoxesPerMode = 16;

private:
	UPROPERTY(EditInstanceOnly, Instanced, Category = "Gaussian Splatting|Selection Boxes",
		meta = (DisplayName = "Cull Selection Boxes", TitleProperty = "SelectionBoxName", NoElementDuplicate))
	TArray<TObjectPtr<UGaussianSplatSelectionBoxComponent>> CullSelectionBoxes;

	UPROPERTY(EditInstanceOnly, Instanced, Category = "Gaussian Splatting|Selection Boxes",
		meta = (DisplayName = "Keep Selection Boxes", TitleProperty = "SelectionBoxName", NoElementDuplicate))
	TArray<TObjectPtr<UGaussianSplatSelectionBoxComponent>> KeepSelectionBoxes;

	UGaussianSplatSelectionBoxComponent* CreateSelectionBox(EGaussianSplatSelectionBoxMode Mode, int32 Index);
	void SynchronizeSelectionBoxes();
	void RemoveInvalidSelectionBoxes();
};
