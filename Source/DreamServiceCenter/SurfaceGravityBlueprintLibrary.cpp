// Copyright (c) 2026. All rights reserved.

#include "SurfaceGravityBlueprintLibrary.h"

#include "CustomGravityComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

namespace SurfaceGravity
{
    constexpr int32 FibonacciProbeCount = 32;
    constexpr float GoldenAngle = 2.39996323f;

    FVector GetCurrentGravityDirection(AActor* TargetActor)
    {
        if (const ACharacter* Character = Cast<ACharacter>(TargetActor))
        {
            if (const UCharacterMovementComponent* Movement =
                Character->GetCharacterMovement())
            {
                const FVector Direction = Movement->GetGravityDirection();
                if (!Direction.IsNearlyZero())
                {
                    return Direction.GetSafeNormal();
                }
            }
        }

        return TargetActor
            ? -TargetActor->GetActorUpVector().GetSafeNormal()
            : FVector::DownVector;
    }

    void AddProbeDirection(
        TArray<FVector, TInlineAllocator<48>>& Directions,
        const FVector& Direction)
    {
        const FVector Normalized = Direction.GetSafeNormal();
        if (Normalized.IsNearlyZero())
        {
            return;
        }

        for (const FVector& Existing : Directions)
        {
            if (Existing.Dot(Normalized) > 0.999f)
            {
                return;
            }
        }

        Directions.Add(Normalized);
    }

    FVector SmoothDirection(
        const FVector& Current,
        const FVector& Desired,
        float DeltaSeconds,
        float InterpSpeed)
    {
        const FVector From = Current.GetSafeNormal();
        const FVector To = Desired.GetSafeNormal();
        if (From.IsNearlyZero() || InterpSpeed <= 0.0f)
        {
            return To;
        }

        const float Alpha = 1.0f - FMath::Exp(
            -FMath::Max(0.0f, InterpSpeed) * FMath::Max(0.0f, DeltaSeconds));
        const FQuat FullRotation = FQuat::FindBetweenNormals(From, To);
        return FQuat::Slerp(FQuat::Identity, FullRotation, Alpha)
            .RotateVector(From)
            .GetSafeNormal();
    }
}

bool USurfaceGravityBlueprintLibrary::SetPlayerGravityFromForwardHit(
    const UObject* WorldContextObject,
    FHitResult& SurfaceHit,
    FVector& NewGravityDirection,
    int32 PlayerIndex,
    float TraceDistance,
    float ProbeRadius,
    TEnumAsByte<ECollisionChannel> TraceChannel,
    bool bDrawDebug)
{
    SurfaceHit = FHitResult();
    NewGravityDirection = FVector::ZeroVector;

    if (!WorldContextObject || TraceDistance <= 0.0f)
    {
        return false;
    }

    UWorld* World = GEngine->GetWorldFromContextObject(
        WorldContextObject,
        EGetWorldErrorMode::ReturnNull);
    const int32 SafePlayerIndex = FMath::Max(0, PlayerIndex);
    ACharacter* Character = UGameplayStatics::GetPlayerCharacter(
        WorldContextObject,
        SafePlayerIndex);
    if (!World || !Character)
    {
        return false;
    }

    FVector ViewLocation;
    FRotator ViewRotation;
    if (APlayerController* PlayerController =
        UGameplayStatics::GetPlayerController(WorldContextObject, SafePlayerIndex))
    {
        PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
    }
    else
    {
        Character->GetActorEyesViewPoint(ViewLocation, ViewRotation);
    }

    const FVector End = ViewLocation +
        ViewRotation.Vector() * FMath::Max(1.0f, TraceDistance);
    FCollisionQueryParams QueryParams(
        SCENE_QUERY_STAT(SetPlayerGravityFromForwardHit),
        false,
        Character);
    QueryParams.AddIgnoredActor(Character);

    const bool bHit = ProbeRadius > KINDA_SMALL_NUMBER
        ? World->SweepSingleByChannel(
            SurfaceHit,
            ViewLocation,
            End,
            FQuat::Identity,
            TraceChannel,
            FCollisionShape::MakeSphere(FMath::Max(0.0f, ProbeRadius)),
            QueryParams)
        : World->LineTraceSingleByChannel(
            SurfaceHit,
            ViewLocation,
            End,
            TraceChannel,
            QueryParams);

    if (bDrawDebug)
    {
        DrawDebugLine(
            World,
            ViewLocation,
            bHit ? SurfaceHit.ImpactPoint : End,
            bHit ? FColor::Green : FColor::Red,
            false,
            2.0f,
            0,
            2.0f);
    }

    if (!bHit || SurfaceHit.ImpactNormal.IsNearlyZero())
    {
        return false;
    }

    NewGravityDirection = -SurfaceHit.ImpactNormal.GetSafeNormal();

    UCustomGravityComponent* GravityComponent =
        Character->FindComponentByClass<UCustomGravityComponent>();
    if (!GravityComponent)
    {
        GravityComponent = NewObject<UCustomGravityComponent>(
            Character,
            UCustomGravityComponent::StaticClass(),
            TEXT("RuntimeManualSurfaceGravity"));
        if (!GravityComponent)
        {
            return false;
        }

        GravityComponent->bApplyInitialGravityOnBeginPlay = false;
        Character->AddInstanceComponent(GravityComponent);
        GravityComponent->RegisterComponent();
    }

    GravityComponent->SetGravityDirection(NewGravityDirection);

    if (bDrawDebug)
    {
        DrawDebugDirectionalArrow(
            World,
            SurfaceHit.ImpactPoint,
            SurfaceHit.ImpactPoint + NewGravityDirection * 150.0f,
            30.0f,
            FColor::Green,
            false,
            2.0f,
            0,
            4.0f);
    }

    return true;
}

FVector USurfaceGravityBlueprintLibrary::FindNearestSurfaceGravityDirection(
    const UObject* WorldContextObject,
    AActor* TargetActor,
    AActor* GravityFieldActor,
    bool& bSurfaceFound,
    FHitResult& SurfaceHit,
    float TraceDistance,
    float ProbeRadius,
    float SurfaceSwitchBias,
    float DirectionInterpSpeed,
    TEnumAsByte<ECollisionChannel> TraceChannel,
    bool bDrawDebug)
{
    bSurfaceFound = false;
    SurfaceHit = FHitResult();

    if (!IsValid(TargetActor))
    {
        return FVector::DownVector;
    }

    UWorld* World = TargetActor->GetWorld();
    if (!World && WorldContextObject)
    {
        World = GEngine->GetWorldFromContextObject(
            WorldContextObject,
            EGetWorldErrorMode::ReturnNull);
    }

    const FVector CurrentGravity =
        SurfaceGravity::GetCurrentGravityDirection(TargetActor);
    if (!World || TraceDistance <= 0.0f)
    {
        return CurrentGravity;
    }

    TArray<FVector, TInlineAllocator<48>> ProbeDirections;
    SurfaceGravity::AddProbeDirection(ProbeDirections, CurrentGravity);
    SurfaceGravity::AddProbeDirection(
        ProbeDirections,
        -TargetActor->GetActorUpVector());
    SurfaceGravity::AddProbeDirection(
        ProbeDirections,
        TargetActor->GetActorUpVector());
    SurfaceGravity::AddProbeDirection(
        ProbeDirections,
        TargetActor->GetActorForwardVector());
    SurfaceGravity::AddProbeDirection(
        ProbeDirections,
        -TargetActor->GetActorForwardVector());
    SurfaceGravity::AddProbeDirection(
        ProbeDirections,
        TargetActor->GetActorRightVector());
    SurfaceGravity::AddProbeDirection(
        ProbeDirections,
        -TargetActor->GetActorRightVector());

    SurfaceGravity::AddProbeDirection(ProbeDirections, FVector::XAxisVector);
    SurfaceGravity::AddProbeDirection(ProbeDirections, -FVector::XAxisVector);
    SurfaceGravity::AddProbeDirection(ProbeDirections, FVector::YAxisVector);
    SurfaceGravity::AddProbeDirection(ProbeDirections, -FVector::YAxisVector);
    SurfaceGravity::AddProbeDirection(ProbeDirections, FVector::ZAxisVector);
    SurfaceGravity::AddProbeDirection(ProbeDirections, -FVector::ZAxisVector);

    for (int32 Index = 0; Index < SurfaceGravity::FibonacciProbeCount; ++Index)
    {
        const float T = (static_cast<float>(Index) + 0.5f) /
            static_cast<float>(SurfaceGravity::FibonacciProbeCount);
        const float Z = 1.0f - (2.0f * T);
        const float Radius = FMath::Sqrt(FMath::Max(0.0f, 1.0f - Z * Z));
        const float Angle = SurfaceGravity::GoldenAngle *
            static_cast<float>(Index);

        SurfaceGravity::AddProbeDirection(
            ProbeDirections,
            FVector(
                Radius * FMath::Cos(Angle),
                Radius * FMath::Sin(Angle),
                Z));
    }

    FCollisionQueryParams QueryParams(
        SCENE_QUERY_STAT(FindNearestSurfaceGravity),
        false,
        TargetActor);
    QueryParams.AddIgnoredActor(TargetActor);
    if (IsValid(GravityFieldActor))
    {
        QueryParams.AddIgnoredActor(GravityFieldActor);
    }

    const FVector Start = TargetActor->GetActorLocation();
    const FCollisionShape ProbeShape = FCollisionShape::MakeSphere(
        FMath::Max(0.0f, ProbeRadius));
    float BestScore = TNumericLimits<float>::Max();
    FHitResult BestHit;

    for (const FVector& Direction : ProbeDirections)
    {
        const FVector End = Start + Direction * TraceDistance;
        FHitResult Hit;
        const bool bHit = ProbeRadius > KINDA_SMALL_NUMBER
            ? World->SweepSingleByChannel(
                Hit,
                Start,
                End,
                FQuat::Identity,
                TraceChannel,
                ProbeShape,
                QueryParams)
            : World->LineTraceSingleByChannel(
                Hit,
                Start,
                End,
                TraceChannel,
                QueryParams);

        if (bDrawDebug)
        {
            DrawDebugLine(
                World,
                Start,
                bHit ? Hit.ImpactPoint : End,
                bHit ? FColor::Cyan : FColor(70, 70, 70),
                false,
                0.0f,
                0,
                0.5f);
        }

        if (!bHit || Hit.ImpactNormal.IsNearlyZero())
        {
            continue;
        }

        const FVector CandidateGravity = -Hit.ImpactNormal.GetSafeNormal();
        const float Continuity = FMath::Max(
            0.0f,
            CandidateGravity.Dot(CurrentGravity));
        const float Score = Hit.Distance -
            FMath::Max(0.0f, SurfaceSwitchBias) *
            FMath::Pow(Continuity, 4.0f);

        if (Score < BestScore)
        {
            BestScore = Score;
            BestHit = Hit;
        }
    }

    if (!BestHit.bBlockingHit)
    {
        return CurrentGravity;
    }

    bSurfaceFound = true;
    SurfaceHit = BestHit;

    if (bDrawDebug)
    {
        DrawDebugSphere(
            World,
            BestHit.ImpactPoint,
            FMath::Max(8.0f, ProbeRadius),
            12,
            FColor::Green,
            false,
            0.0f,
            0,
            2.0f);
        DrawDebugDirectionalArrow(
            World,
            Start,
            Start - BestHit.ImpactNormal.GetSafeNormal() * 120.0f,
            30.0f,
            FColor::Green,
            false,
            0.0f,
            0,
            3.0f);
    }

    return SurfaceGravity::SmoothDirection(
        CurrentGravity,
        -BestHit.ImpactNormal,
        World->GetDeltaSeconds(),
        DirectionInterpSpeed);
}
