#include "LetterInspectionWorldSubsystem.h"

#include "LetterInspectComponent.h"

#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "HAL/IConsoleManager.h"


static TAutoConsoleVariable<int32> CVarLetterInspectionAutoBootstrap(
    TEXT("LetterInspection.AutoBootstrap"),
    1,
    TEXT("Automatically add LetterInspectComponent to the local player pawn (0/1)."),
    ECVF_Default
);


void ULetterInspectionWorldSubsystem::Tick(float DeltaTime)
{
    if (CVarLetterInspectionAutoBootstrap.GetValueOnGameThread() == 0)
    {
        return;
    }


    RetryCountdown -= DeltaTime;


    if (
        RetryCountdown <= 0.0f ||
        !CachedPawn.IsValid() ||
        !CachedComponent.IsValid()
        )
    {
        EnsurePlayerComponent();
        RetryCountdown = 0.5f;
    }
}


TStatId ULetterInspectionWorldSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(
        ULetterInspectionWorldSubsystem,
        STATGROUP_Tickables
    );
}


bool ULetterInspectionWorldSubsystem::DoesSupportWorldType(
    EWorldType::Type WorldType
) const
{
    return
        WorldType == EWorldType::Game ||
        WorldType == EWorldType::PIE;
}


void ULetterInspectionWorldSubsystem::EnsurePlayerComponent()
{
    UWorld* World = GetWorld();


    if (!IsValid(World))
    {
        return;
    }


    APlayerController* PlayerController =
        World->GetFirstPlayerController();


    APawn* PlayerPawn =
        IsValid(PlayerController)
        ? PlayerController->GetPawn()
        : nullptr;


    if (!IsValid(PlayerPawn) || !PlayerPawn->IsLocallyControlled())
    {
        CachedPawn.Reset();
        CachedComponent.Reset();
        return;
    }


    if (
        CachedPawn.Get() == PlayerPawn &&
        CachedComponent.IsValid()
        )
    {
        return;
    }


    ULetterInspectComponent* Component =
        PlayerPawn->FindComponentByClass<ULetterInspectComponent>();


    if (!IsValid(Component))
    {
        Component = NewObject<ULetterInspectComponent>(
            PlayerPawn,
            ULetterInspectComponent::StaticClass(),
            TEXT("AutoLetterInspectComponent"),
            RF_Transient
        );


        if (!IsValid(Component))
        {
            return;
        }


        PlayerPawn->AddInstanceComponent(Component);
        Component->RegisterComponent();


        UE_LOG(
            LogTemp,
            Log,
            TEXT("[LetterInspect] Auto component added to %s."),
            *PlayerPawn->GetName()
        );
    }


    Component->EnsureAutoInitialized();


    CachedPawn = PlayerPawn;
    CachedComponent = Component;
}
