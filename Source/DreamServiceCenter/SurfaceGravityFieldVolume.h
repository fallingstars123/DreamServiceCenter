// Copyright (c) 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurfaceGravityFieldVolume.generated.h"

class ACharacter;
class UBoxComponent;
class UCustomGravityComponent;

/**
 * A placeable volume that pulls characters toward the closest blocking surface.
 *
 * This is intentionally separate from BP_GravityFeild_Sphere: the surface volume
 * can cover a whole PCG level while an overlapping radial sphere keeps priority.
 */
UCLASS(Blueprintable, meta = (DisplayName = "Surface Gravity Field Volume"))
class DREAMSERVICECENTER_API ASurfaceGravityFieldVolume : public AActor
{
	GENERATED_BODY()

public:
	ASurfaceGravityFieldVolume();

	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Resize this box in the level to cover only the surface-gravity space. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Surface Gravity")
	TObjectPtr<UBoxComponent> GravityBounds;

	/** Disabled by default: manual forward-hit gravity is the preferred mode. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surface Gravity")
	bool bAutomaticSurfaceGravity = false;

	/** Maximum distance at which a floor, wall or ceiling can attract the player. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Surface Gravity|Detection",
		meta = (ClampMin = "10.0", UIMin = "50.0", UIMax = "1500.0"))
	float TraceDistance = 450.0f;

	/** Radius of each surface probe. A small sweep is more reliable than a line. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Surface Gravity|Detection",
		meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "100.0"))
	float ProbeRadius = 20.0f;

	/** Keeps the current surface until a new one is meaningfully closer. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Surface Gravity|Detection",
		meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "200.0"))
	float SurfaceSwitchBias = 45.0f;

	/** Larger values rotate gravity faster when changing from floor to wall. */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Surface Gravity|Movement",
		meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "30.0"))
	float DirectionInterpSpeed = 8.0f;

	/** Collision channel used to find PCG surfaces. LE2_JIN already blocks Visibility. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surface Gravity|Detection")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	/** BP_GravityFeild_Sphere wins when the player overlaps both field types. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surface Gravity|Priority")
	bool bRadialSphereTakesPriority = true;

	/** Only player-controlled characters are affected when enabled. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surface Gravity|Filter")
	bool bOnlyAffectPlayers = true;

	/** Restore this gravity after leaving the volume. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surface Gravity|Exit")
	bool bResetGravityOnExit = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surface Gravity|Exit")
	FVector ExitGravityDirection = FVector::DownVector;

	/** Draw all probes and the selected surface during PIE. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surface Gravity|Debug")
	bool bDrawDebug = false;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void HandleEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex);

private:
	UCustomGravityComponent* ResolveGravityComponent(ACharacter* Character);
	AActor* FindOverlappingRadialField(ACharacter* Character) const;
	void RemoveCharacter(ACharacter* Character, bool bApplyExitGravity);

	TArray<TWeakObjectPtr<ACharacter>> CharactersInside;
};
