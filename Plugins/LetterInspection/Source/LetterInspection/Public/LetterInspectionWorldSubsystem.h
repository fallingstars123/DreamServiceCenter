#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "LetterInspectionWorldSubsystem.generated.h"


class APawn;
class ULetterInspectComponent;


/**
 * Runtime bootstrap for the project integration.
 *
 * It adds one transient LetterInspectComponent to the locally controlled pawn,
 * so BP_Astronaut does not need a binary Blueprint rewrite just to use scanning.
 */
UCLASS()
class LETTERINSPECTION_API ULetterInspectionWorldSubsystem
    : public UTickableWorldSubsystem
{
    GENERATED_BODY()


public:

    virtual void Tick(float DeltaTime) override;

    virtual TStatId GetStatId() const override;

    virtual bool DoesSupportWorldType(
        EWorldType::Type WorldType
    ) const override;


private:

    void EnsurePlayerComponent();


    TWeakObjectPtr<APawn> CachedPawn;

    TWeakObjectPtr<ULetterInspectComponent> CachedComponent;

    float RetryCountdown = 0.0f;
};
