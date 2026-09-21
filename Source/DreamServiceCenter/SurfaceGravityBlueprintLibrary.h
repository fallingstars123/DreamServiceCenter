// Copyright (c) 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurfaceGravityBlueprintLibrary.generated.h"

/** Blueprint helpers for Spider-Man-style nearest-surface gravity. */
UCLASS()
class DREAMSERVICECENTER_API USurfaceGravityBlueprintLibrary
    : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
	/**
	 * Trace from the active first-person camera and, when a blocking surface is
	 * hit, point the player's gravity into that surface. Nothing changes when
	 * the trace misses. Intended for an explicit input such as the L key.
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "Custom Gravity|Manual Surface",
		meta = (
			DisplayName = "Set Player Gravity From Forward Hit",
			WorldContext = "WorldContextObject",
			AdvancedDisplay = "PlayerIndex,TraceDistance,ProbeRadius,TraceChannel,bDrawDebug"
		)
	)
	static bool SetPlayerGravityFromForwardHit(
		const UObject* WorldContextObject,
		FHitResult& SurfaceHit,
		FVector& NewGravityDirection,
		int32 PlayerIndex = 0,
		float TraceDistance = 1200.0f,
		float ProbeRadius = 8.0f,
		TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility,
		bool bDrawDebug = false
	);

    /**
     * Probe around TargetActor and return gravity toward the closest blocking
     * surface. The actor using this direction can walk on floors, walls and
     * ceilings. Current character gravity is biased slightly to prevent rapid
     * switching at corners, and the returned direction is smoothly rotated.
     */
    UFUNCTION(
        BlueprintCallable,
        Category = "Custom Gravity|Surface",
        meta = (
            DisplayName = "Find Nearest Surface Gravity",
            WorldContext = "WorldContextObject",
            AdvancedDisplay = "GravityFieldActor,TraceDistance,ProbeRadius,SurfaceSwitchBias,DirectionInterpSpeed,TraceChannel,bDrawDebug"
        )
    )
    static FVector FindNearestSurfaceGravityDirection(
        const UObject* WorldContextObject,
        AActor* TargetActor,
        AActor* GravityFieldActor,
        bool& bSurfaceFound,
        FHitResult& SurfaceHit,
        float TraceDistance = 600.0f,
        float ProbeRadius = 24.0f,
        float SurfaceSwitchBias = 40.0f,
        float DirectionInterpSpeed = 12.0f,
        TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility,
        bool bDrawDebug = false
    );
};
