// Copyright (c) 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CustomGravityComponent.h"
#include "GameFramework/Actor.h"
#include "CustomGravityGameManager.generated.h"

class ACharacter;

/**
 * Level-placeable Blueprint entry point for custom gravity.
 *
 * The manager never polls input and never changes gravity by itself. Place one
 * in the persistent level, keep a Blueprint reference (or Get Actor Of Class),
 * then call the functions below from any gameplay Blueprint.
 */
UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Custom Gravity Game Manager"))
class DREAMSERVICECENTER_API ACustomGravityGameManager : public AActor
{
	GENERATED_BODY()

public:
	ACustomGravityGameManager();

	/** Optional explicit target. When empty, PlayerIndex is resolved. */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Custom Gravity|Target")
	TObjectPtr<ACharacter> TargetCharacter;

	/** Local player used when TargetCharacter is empty. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Gravity|Target", meta = (ClampMin = "0"))
	int32 PlayerIndex = 0;

	/** Add CustomGravityComponent at runtime if the target character has none. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Gravity|Target")
	bool bAutoCreateComponentIfMissing = true;

	/** Resolve the current character and its gravity component. */
	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Manager")
	UCustomGravityComponent* ResolveGravityComponent();

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Manager")
	bool SetPlayerGravityDirection(FVector NewGravityDirection);

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Manager")
	bool SetPlayerGravityScale(float NewGravityScale);

	/** Set the maximum speed along gravity in cm/s. Zero disables the limit. */
	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Manager")
	bool SetPlayerMaxGravityFallSpeed(float NewMaxGravityFallSpeed);

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Manager")
	bool SetPlayerGravityPreset(ECustomGravityPreset Preset);

	/** Valid values are 1 through 6. */
	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Manager")
	bool SetPlayerGravityByNumber(int32 GravityNumber);

	/**
	 * Three-button gravity control. AxisNumber uses 1=X, 2=Y, 3=Z.
	 * Pressing the same axis again reverses its sign. When changing to a
	 * different axis, that axis starts in its negative direction.
	 */
	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Three Button")
	bool TogglePlayerGravityAxisByNumber(int32 AxisNumber);

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Three Button", meta = (DisplayName = "Toggle Player Gravity 1 - X Axis"))
	bool TogglePlayerGravityX();

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Three Button", meta = (DisplayName = "Toggle Player Gravity 2 - Y Axis"))
	bool TogglePlayerGravityY();

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Three Button", meta = (DisplayName = "Toggle Player Gravity 3 - Z Axis"))
	bool TogglePlayerGravityZ();

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Manager", meta = (DisplayName = "Set Player Gravity 1 - Floor (-Z)"))
	bool Gravity1();

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Manager", meta = (DisplayName = "Set Player Gravity 2 - Ceiling (+Z)"))
	bool Gravity2();

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Manager", meta = (DisplayName = "Set Player Gravity 3 - World +X"))
	bool Gravity3();

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Manager", meta = (DisplayName = "Set Player Gravity 4 - World -X"))
	bool Gravity4();

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Manager", meta = (DisplayName = "Set Player Gravity 5 - World +Y"))
	bool Gravity5();

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Manager", meta = (DisplayName = "Set Player Gravity 6 - World -Y"))
	bool Gravity6();

	UFUNCTION(BlueprintPure, Category = "Custom Gravity|Manager")
	FVector GetPlayerGravityDirection() const;

private:
	ACharacter* ResolveTargetCharacter();
	bool TogglePlayerGravityOnAxis(const FVector& PositiveAxis);

	UPROPERTY(Transient)
	TObjectPtr<UCustomGravityComponent> CachedGravityComponent;
};
