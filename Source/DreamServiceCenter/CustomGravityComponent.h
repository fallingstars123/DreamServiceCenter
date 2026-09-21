// Copyright (c) 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomGravityComponent.generated.h"

class ACharacter;
class UCharacterMovementComponent;

/** Six world-space directions exposed as the 1-6 gravity presets. */
UENUM(BlueprintType)
enum class ECustomGravityPreset : uint8
{
	WorldNegativeZ UMETA(DisplayName = "1 - Floor (-Z)"),
	WorldPositiveZ UMETA(DisplayName = "2 - Ceiling (+Z)"),
	WorldPositiveX UMETA(DisplayName = "3 - World +X"),
	WorldNegativeX UMETA(DisplayName = "4 - World -X"),
	WorldPositiveY UMETA(DisplayName = "5 - World +Y"),
	WorldNegativeY UMETA(DisplayName = "6 - World -Y")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnCustomGravityChanged,
	FVector,
	NewGravityDirection);

/**
 * Blueprint-friendly custom gravity for ACharacter on UE 5.8.
 *
 * This component deliberately uses UCharacterMovementComponent::SetGravityDirection.
 * It therefore keeps walking, falling, floor tests, jumping, and movement prediction in
 * CharacterMovement instead of applying a second physics force to the capsule.
 */
UCLASS(ClassGroup = (Movement), meta = (BlueprintSpawnableComponent, DisplayName = "Custom Gravity (UE 5.8)"))
class DREAMSERVICECENTER_API UCustomGravityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCustomGravityComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(
		TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Gravity used at BeginPlay. It is normalized before being applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Gravity")
	FVector InitialGravityDirection = FVector(0.0, 0.0, -1.0);

	/** Apply InitialGravityDirection when play starts. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Gravity")
	bool bApplyInitialGravityOnBeginPlay = true;

	/** Multiplier for the world gravity magnitude. Direction is controlled separately. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		ReplicatedUsing = OnRep_GravityScale,
		Category = "Custom Gravity",
		meta = (ClampMin = "0.0", ClampMax = "20.0", UIMin = "0.0", UIMax = "5.0"))
	float GravityScale = 0.5f;

	/** Rotate the character capsule so its local Up points away from gravity. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Gravity|Alignment")
	bool bAlignCharacterToGravity = true;

	/** Degrees per second used to align the capsule. Zero means instant alignment. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Custom Gravity|Alignment",
		meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1080.0"))
	float AlignmentSpeed = 540.0f;

	/** Preserve the first-person view orientation when gravity changes. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Gravity|Alignment")
	bool bRotateControllerOnGravityChange = true;

	/** Leave the previous floor immediately so CharacterMovement can find the new one. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Gravity|Movement")
	bool bForceFallingOnGravityChange = true;

	/**
	 * Maximum velocity along the active gravity direction, in cm/s.
	 * Set to zero to disable the limit. This does not affect sideways or
	 * upward velocity.
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Custom Gravity|Movement",
		meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "4000.0"))
	float MaxGravityFallSpeed = 1200.0f;

	/** Current normalized direction in which gravity pulls. */
	UPROPERTY(
		VisibleInstanceOnly,
		BlueprintReadOnly,
		ReplicatedUsing = OnRep_GravityDirection,
		Category = "Custom Gravity")
	FVector CurrentGravityDirection = FVector(0.0, 0.0, -1.0);

	/** Fired after this component applies a different direction. */
	UPROPERTY(BlueprintAssignable, Category = "Custom Gravity")
	FOnCustomGravityChanged OnGravityChanged;

	/** Set any non-zero world-space gravity direction. Magnitude is ignored. */
	UFUNCTION(BlueprintCallable, Category = "Custom Gravity")
	void SetGravityDirection(FVector NewGravityDirection);

	/** Change gravity magnitude without changing its direction. */
	UFUNCTION(BlueprintCallable, Category = "Custom Gravity")
	void SetGravityScale(float NewGravityScale);

	/** Set the maximum speed along gravity. Zero disables the speed limit. */
	UFUNCTION(BlueprintCallable, Category = "Custom Gravity|Movement")
	void SetMaxGravityFallSpeed(float NewMaxGravityFallSpeed);

	/** Apply one of the six named directions. */
	UFUNCTION(BlueprintCallable, Category = "Custom Gravity")
	void SetGravityPreset(ECustomGravityPreset Preset);

	/**
	 * Blueprint/input convenience entry point. Valid values are 1 through 6.
	 * Returns false and makes no change for any other value.
	 */
	UFUNCTION(BlueprintCallable, Category = "Custom Gravity")
	bool SetGravityByNumber(int32 GravityNumber);

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity", meta = (DisplayName = "Gravity 1 - Floor (-Z)"))
	void Gravity1();

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity", meta = (DisplayName = "Gravity 2 - Ceiling (+Z)"))
	void Gravity2();

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity", meta = (DisplayName = "Gravity 3 - World +X"))
	void Gravity3();

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity", meta = (DisplayName = "Gravity 4 - World -X"))
	void Gravity4();

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity", meta = (DisplayName = "Gravity 5 - World +Y"))
	void Gravity5();

	UFUNCTION(BlueprintCallable, Category = "Custom Gravity", meta = (DisplayName = "Gravity 6 - World -Y"))
	void Gravity6();

	UFUNCTION(BlueprintPure, Category = "Custom Gravity")
	FVector GetGravityDirection() const;

	UFUNCTION(BlueprintPure, Category = "Custom Gravity")
	static FVector GetDirectionForPreset(ECustomGravityPreset Preset);

protected:
	UFUNCTION()
	void OnRep_GravityDirection();

	UFUNCTION()
	void OnRep_GravityScale();

	UFUNCTION(Server, Reliable)
	void ServerSetGravityDirection(FVector NewGravityDirection);

	UFUNCTION(Server, Reliable)
	void ServerSetGravityScale(float NewGravityScale);

private:
	bool ResolveCharacterAndMovement();
	void ApplyGravityDirection(const FVector& NewGravityDirection, bool bBroadcastChange);
	void ClampGravityFallSpeed();
	void AlignCharacter(float DeltaTime, bool bInstant);
	void RotateController(const FVector& PreviousDirection, const FVector& NewDirection);
	UPROPERTY(Transient)
	TObjectPtr<ACharacter> CharacterOwner;

	UPROPERTY(Transient)
	TObjectPtr<UCharacterMovementComponent> CharacterMovement;
};
