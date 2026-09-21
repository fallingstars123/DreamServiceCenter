#include "LetterInspectComponent.h"

#include "InspectableLetter.h"
#include "LetterDescriptionWidget.h"

#include "Camera/CameraComponent.h"

#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SpotLightComponent.h"

#include "Engine/World.h"
#include "Engine/EngineTypes.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

#include "Blueprint/UserWidget.h"
#include "InputCoreTypes.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/UnrealType.h"


// =========================================================
// Constructor
// =========================================================

ULetterInspectComponent::ULetterInspectComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;

    ScanToggleKey = EKeys::F;
    ScanHoldKey = EKeys::LeftMouseButton;
    InspectExitKey = EKeys::Escape;
    InspectSecondaryExitKey = EKeys::RightMouseButton;


    static ConstructorHelpers::FClassFinder<ULetterDescriptionWidget>
        DefaultDescriptionWidget(
            TEXT("/LetterInspection/Widgets/MyLetterDescriptionWidget")
        );


    if (DefaultDescriptionWidget.Succeeded())
    {
        DescriptionWidgetClass = DefaultDescriptionWidget.Class;
    }
}


// =========================================================
// BeginPlay
// =========================================================

void ULetterInspectComponent::BeginPlay()
{
    Super::BeginPlay();


    PlayerController =
        ResolvePlayerController();


    if (bAutoInitializeFromOwner)
    {
        AutoInitializeInspectSystem();
    }
}


// =========================================================
// EndPlay
// =========================================================

void ULetterInspectComponent::EndPlay(
    const EEndPlayReason::Type EndPlayReason
)
{
    RestoreScanHighlight();
    RestoreMainProjectUI();


    Super::EndPlay(EndPlayReason);
}


// =========================================================
// Tick
// =========================================================

void ULetterInspectComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction
)
{
    Super::TickComponent(
        DeltaTime,
        TickType,
        ThisTickFunction
    );


    if (bUseDefaultScanInput)
    {
        PollDefaultScanInput();
    }


    if (
        bIsInspecting &&
        bHardLockViewRotation &&
        IsValid(PlayerController)
        )
    {
        PlayerController->SetControlRotation(
            LockedControlRotation
        );
    }


    UpdateLetterScan(DeltaTime);
}


// =========================================================
// Initialize
// =========================================================

void ULetterInspectComponent::InitializeInspectSystem(
    UCameraComponent* InCamera,
    USceneComponent* InInspectPoint
)
{
    ViewCamera =
        InCamera;


    InspectPoint =
        InInspectPoint;


    PlayerController =
        ResolvePlayerController();


    // ---------------------------------------------------------
    // 创建阅读灯
    // ---------------------------------------------------------

    CreateInspectLight();


    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "[LetterInspect] Init Camera=%s InspectPoint=%s"
        ),
        ViewCamera
        ? *ViewCamera->GetName()
        : TEXT("NULL"),

        InspectPoint
        ? *InspectPoint->GetName()
        : TEXT("NULL")
    );
}


// =========================================================
// Is Initialized
// =========================================================

bool ULetterInspectComponent::IsInitialized() const
{
    return
        IsValid(ViewCamera) &&
        IsValid(InspectPoint);
}


void ULetterInspectComponent::EnsureAutoInitialized()
{
    if (!IsInitialized())
    {
        AutoInitializeInspectSystem();
    }
}


// =========================================================
// Auto Initialize
// =========================================================

void ULetterInspectComponent::AutoInitializeInspectSystem()
{
    if (IsInitialized())
    {
        return;
    }


    AActor* OwnerActor = GetOwner();


    if (!IsValid(OwnerActor))
    {
        return;
    }


    TInlineComponentArray<UCameraComponent*> Cameras;
    OwnerActor->GetComponents(Cameras);


    UCameraComponent* SelectedCamera = nullptr;


    for (UCameraComponent* Camera : Cameras)
    {
        if (IsValid(Camera) && Camera->IsActive())
        {
            SelectedCamera = Camera;
            break;
        }
    }


    if (!IsValid(SelectedCamera) && Cameras.Num() > 0)
    {
        SelectedCamera = Cameras[0];
    }


    if (!IsValid(SelectedCamera))
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("[LetterInspect] Auto initialize failed: owner has no CameraComponent.")
        );


        return;
    }


    AutoInspectPoint =
        NewObject<USceneComponent>(
            OwnerActor,
            USceneComponent::StaticClass(),
            TEXT("LetterAutoInspectPoint")
        );


    if (!IsValid(AutoInspectPoint))
    {
        return;
    }


    OwnerActor->AddInstanceComponent(AutoInspectPoint);
    AutoInspectPoint->RegisterComponent();
    AutoInspectPoint->AttachToComponent(
        SelectedCamera,
        FAttachmentTransformRules::KeepRelativeTransform
    );
    AutoInspectPoint->SetRelativeLocation(AutoInspectPointOffset);
    AutoInspectPoint->SetRelativeRotation(FRotator::ZeroRotator);


    InitializeInspectSystem(
        SelectedCamera,
        AutoInspectPoint
    );
}


// =========================================================
// Scan Public API
// =========================================================

void ULetterInspectComponent::SetScanModeActive(bool bActive)
{
    if (bScanModeActive == bActive)
    {
        return;
    }


    if (bActive && !IsInitialized() && bAutoInitializeFromOwner)
    {
        AutoInitializeInspectSystem();
    }


    bScanModeActive = bActive;


    if (!bScanModeActive)
    {
        bScanInputHeld = false;
        SetScanTargetInternal(nullptr);
        ResetScanProgress();
    }


    OnScanModeChanged.Broadcast(bScanModeActive);


    UE_LOG(
        LogTemp,
        Log,
        TEXT("[LetterInspect] Scan mode: %s"),
        bScanModeActive ? TEXT("ON") : TEXT("OFF")
    );
}


void ULetterInspectComponent::ToggleScanMode()
{
    SetScanModeActive(!bScanModeActive);
}


void ULetterInspectComponent::SetScanInputHeld(bool bHeld)
{
    bScanInputHeld = bHeld;


    if (!bScanInputHeld)
    {
        bScanCompletedForCurrentTarget = false;
    }
}


// =========================================================
// Default Input
// =========================================================

void ULetterInspectComponent::PollDefaultScanInput()
{
    if (!IsValid(PlayerController))
    {
        PlayerController = ResolvePlayerController();
    }


    if (!IsValid(PlayerController))
    {
        return;
    }


    const bool bExitInspectRequested =
        bIsInspecting &&
        (
            (
                InspectExitKey.IsValid() &&
                PlayerController->WasInputKeyJustPressed(InspectExitKey)
            ) ||
            (
                InspectSecondaryExitKey.IsValid() &&
                PlayerController->WasInputKeyJustPressed(InspectSecondaryExitKey)
            ) ||
            (
                ScanToggleKey.IsValid() &&
                PlayerController->WasInputKeyJustPressed(ScanToggleKey)
            )
        );


    if (bExitInspectRequested)
    {
        EndInspect();
        return;
    }


    if (
        ScanToggleKey.IsValid() &&
        PlayerController->WasInputKeyJustPressed(ScanToggleKey)
        )
    {
        ToggleScanMode();
    }


    const bool bHoldKeyDown =
        ScanHoldKey.IsValid() &&
        PlayerController->IsInputKeyDown(ScanHoldKey);


    SetScanInputHeld(bHoldKeyDown);
}


// =========================================================
// Scan Update
// =========================================================

void ULetterInspectComponent::UpdateLetterScan(float DeltaTime)
{
    if (
        !bScanModeActive ||
        bIsInspecting ||
        !IsInitialized()
        )
    {
        return;
    }


    AInspectableLetter* Candidate =
        TraceForInspectableLetter();


    if (IsValid(Candidate))
    {
        ScanTargetLostTime = 0.0f;


        if (Candidate != ScanTarget)
        {
            SetScanTargetInternal(Candidate);
        }
    }
    else if (IsValid(ScanTarget))
    {
        ScanTargetLostTime += DeltaTime;


        if (ScanTargetLostTime >= ScanTargetGracePeriod)
        {
            SetScanTargetInternal(nullptr);
        }
    }


    const float PreviousProgress = ScanProgress;


    if (
        IsValid(ScanTarget) &&
        bScanInputHeld &&
        !bScanCompletedForCurrentTarget
        )
    {
        const float SafeDuration = FMath::Max(ScanDuration, 0.01f);


        ScanProgress = FMath::Clamp(
            ScanProgress + DeltaTime / SafeDuration,
            0.0f,
            1.0f
        );
    }
    else if (!bScanInputHeld && ScanProgress > 0.0f)
    {
        ScanProgress = FMath::Max(
            0.0f,
            ScanProgress - ScanProgressDecayPerSecond * DeltaTime
        );
    }


    if (!FMath::IsNearlyEqual(PreviousProgress, ScanProgress))
    {
        OnScanProgressChanged.Broadcast(
            ScanTarget,
            ScanProgress
        );
    }


    if (
        IsValid(ScanTarget) &&
        ScanProgress >= 1.0f &&
        !bScanCompletedForCurrentTarget
        )
    {
        bScanCompletedForCurrentTarget = true;


        AInspectableLetter* CompletedTarget = ScanTarget;
        OnScanCompleted.Broadcast(CompletedTarget);


        if (bAutoBeginInspectOnScanComplete)
        {
            BeginInspect(CompletedTarget);
        }
    }
}


// =========================================================
// Scan Trace
// =========================================================

AInspectableLetter*
ULetterInspectComponent::TraceForInspectableLetter() const
{
    if (!IsValid(ViewCamera) || !GetWorld())
    {
        return nullptr;
    }


    const FVector TraceStart =
        ViewCamera->GetComponentLocation();


    const FVector TraceEnd =
        TraceStart +
        ViewCamera->GetForwardVector() *
        FMath::Max(ScanDistance, 1.0f);


    FCollisionQueryParams QueryParams(
        SCENE_QUERY_STAT(LetterInspectionScan),
        false,
        GetOwner()
    );


    if (IsValid(CurrentLetter))
    {
        QueryParams.AddIgnoredActor(CurrentLetter);
    }


    FHitResult Hit;
    bool bHit = false;


    if (ScanRadius > KINDA_SMALL_NUMBER)
    {
        bHit = GetWorld()->SweepSingleByChannel(
            Hit,
            TraceStart,
            TraceEnd,
            FQuat::Identity,
            ScanTraceChannel,
            FCollisionShape::MakeSphere(ScanRadius),
            QueryParams
        );
    }
    else
    {
        bHit = GetWorld()->LineTraceSingleByChannel(
            Hit,
            TraceStart,
            TraceEnd,
            ScanTraceChannel,
            QueryParams
        );
    }


    return bHit
        ? ResolveInspectableLetter(Hit.GetActor())
        : nullptr;
}


AInspectableLetter*
ULetterInspectComponent::ResolveInspectableLetter(
    AActor* HitActor
) const
{
    AActor* Candidate = HitActor;


    for (int32 ParentDepth = 0; Candidate && ParentDepth < 8; ++ParentDepth)
    {
        if (AInspectableLetter* Letter = Cast<AInspectableLetter>(Candidate))
        {
            return Letter;
        }


        Candidate = Candidate->GetAttachParentActor();
    }


    return nullptr;
}


// =========================================================
// Scan Target / Highlight
// =========================================================

void ULetterInspectComponent::SetScanTargetInternal(
    AInspectableLetter* NewTarget
)
{
    if (ScanTarget == NewTarget)
    {
        return;
    }


    AInspectableLetter* PreviousTarget = ScanTarget;


    RestoreScanHighlight();


    ScanTarget = NewTarget;
    ScanTargetLostTime = 0.0f;
    bScanCompletedForCurrentTarget = false;
    ResetScanProgress();


    ApplyScanHighlight(ScanTarget);


    OnScanTargetChanged.Broadcast(
        ScanTarget,
        PreviousTarget
    );
}


void ULetterInspectComponent::ApplyScanHighlight(
    AInspectableLetter* Target
)
{
    if (!bHighlightScanTarget || !IsValid(Target))
    {
        return;
    }


    HighlightedPrimitive = FindLetterPrimitive(Target);


    if (!IsValid(HighlightedPrimitive))
    {
        return;
    }


    bOriginalRenderCustomDepth =
        HighlightedPrimitive->bRenderCustomDepth;


    OriginalCustomDepthStencilValue =
        HighlightedPrimitive->CustomDepthStencilValue;


    HighlightedPrimitive->SetRenderCustomDepth(true);
    HighlightedPrimitive->SetCustomDepthStencilValue(
        FMath::Clamp(ScanCustomDepthStencilValue, 0, 255)
    );
}


void ULetterInspectComponent::RestoreScanHighlight()
{
    if (!IsValid(HighlightedPrimitive))
    {
        HighlightedPrimitive = nullptr;
        return;
    }


    HighlightedPrimitive->SetCustomDepthStencilValue(
        OriginalCustomDepthStencilValue
    );
    HighlightedPrimitive->SetRenderCustomDepth(
        bOriginalRenderCustomDepth
    );


    HighlightedPrimitive = nullptr;
}


void ULetterInspectComponent::ResetScanProgress()
{
    if (FMath::IsNearlyZero(ScanProgress))
    {
        ScanProgress = 0.0f;
        return;
    }


    ScanProgress = 0.0f;
    OnScanProgressChanged.Broadcast(
        ScanTarget,
        ScanProgress
    );
}


// =========================================================
// Resolve Player Controller
// =========================================================

APlayerController*
ULetterInspectComponent::ResolvePlayerController()
{
    if (
        APawn* PawnOwner =
        Cast<APawn>(
            GetOwner()
        )
        )
    {
        if (
            APlayerController* PC =
            Cast<APlayerController>(
                PawnOwner->GetController()
            )
            )
        {
            return PC;
        }
    }


    if (GetWorld())
    {
        return
            GetWorld()
            ->GetFirstPlayerController();
    }


    return nullptr;
}


// =========================================================
// Begin Inspect
// =========================================================

bool ULetterInspectComponent::BeginInspect(
    AInspectableLetter* Letter
)
{
    // ---------------------------------------------------------
    // Setup
    // ---------------------------------------------------------

    if (!IsInitialized())
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "[LetterInspect] BeginInspect Failed - "
                "Camera or InspectPoint is NULL."
            )
        );


        return false;
    }


    // ---------------------------------------------------------
    // Letter
    // ---------------------------------------------------------

    if (!IsValid(Letter))
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "[LetterInspect] BeginInspect Failed - "
                "Letter is NULL."
            )
        );


        return false;
    }


    // ---------------------------------------------------------
    // Already Inspecting Same Letter
    // ---------------------------------------------------------

    if (
        bIsInspecting &&
        CurrentLetter == Letter
        )
    {
        return true;
    }


    // ---------------------------------------------------------
    // Inspecting Another Letter
    // ---------------------------------------------------------

    if (bIsInspecting)
    {
        EndInspect();
    }


    // ---------------------------------------------------------
    // Current Letter
    // ---------------------------------------------------------

    CurrentLetter =
        Letter;


    bIsInspecting =
        true;


    // The close-up view is its own mode. Stop the plugin scan loop so the
    // current target cannot immediately retrigger while it is being inspected.
    SetScanModeActive(false);


    // ---------------------------------------------------------
    // Save Original State
    // ---------------------------------------------------------

    SaveLetterState();


    // ---------------------------------------------------------
    // Move To Camera
    // ---------------------------------------------------------

    MoveLetterToInspectPoint();


    // ---------------------------------------------------------
    // Depth Of Field
    // ---------------------------------------------------------

    EnableInspectDepthOfField();


    // ---------------------------------------------------------
    // Soft Inspect Light
    // ---------------------------------------------------------

    EnableInspectLight();


    // ---------------------------------------------------------
    // UI
    // ---------------------------------------------------------

    HideMainProjectUI();

    CreateDescriptionWidget();


    // ---------------------------------------------------------
    // Lock Player
    // ---------------------------------------------------------

    LockPlayerControl();


    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "[LetterInspect] Begin Inspect: %s"
        ),
        *Letter->GetName()
    );


    return true;
}


// =========================================================
// End Inspect
// =========================================================

void ULetterInspectComponent::EndInspect()
{
    if (!bIsInspecting)
    {
        return;
    }


    // ---------------------------------------------------------
    // UI
    // ---------------------------------------------------------

    RemoveDescriptionWidget();

    RestoreMainProjectUI();


    // ---------------------------------------------------------
    // Light
    // ---------------------------------------------------------

    DisableInspectLight();


    // ---------------------------------------------------------
    // Letter
    // ---------------------------------------------------------

    RestoreLetterState();


    // ---------------------------------------------------------
    // Camera
    // ---------------------------------------------------------

    RestoreCameraPostProcess();


    // ---------------------------------------------------------
    // Player
    // ---------------------------------------------------------

    RestorePlayerControl();


    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "[LetterInspect] End Inspect"
        )
    );


    CurrentLetter =
        nullptr;


    LetterPrimitive =
        nullptr;


    bIsInspecting =
        false;
}


// =========================================================
// Find Primitive
// =========================================================

UPrimitiveComponent*
ULetterInspectComponent::FindLetterPrimitive(
    AInspectableLetter* Letter
) const
{
    if (!IsValid(Letter))
    {
        return nullptr;
    }


    return Letter->GetActiveLetterPrimitive();
}


// =========================================================
// Save Letter State
// =========================================================

void ULetterInspectComponent::SaveLetterState()
{
    if (!IsValid(CurrentLetter))
    {
        return;
    }


    // ---------------------------------------------------------
    // Transform
    // ---------------------------------------------------------

    OriginalLetterTransform =
        CurrentLetter->GetActorTransform();


    // ---------------------------------------------------------
    // Attachment
    // ---------------------------------------------------------

    USceneComponent* Root =
        CurrentLetter->GetRootComponent();


    OriginalAttachParent =
        Root
        ? Root->GetAttachParent()
        : nullptr;


    OriginalAttachSocket =
        Root
        ? Root->GetAttachSocketName()
        : NAME_None;


    // ---------------------------------------------------------
    // Physics
    // ---------------------------------------------------------

    LetterPrimitive =
        FindLetterPrimitive(
            CurrentLetter
        );


    if (IsValid(LetterPrimitive))
    {
        bOriginalSimulatePhysics =
            LetterPrimitive
            ->IsSimulatingPhysics();


        bOriginalGravity =
            LetterPrimitive
            ->IsGravityEnabled();


        LetterPrimitive
            ->SetSimulatePhysics(false);


        LetterPrimitive
            ->SetEnableGravity(false);
    }
}


// =========================================================
// Move Letter To Inspect Point
// =========================================================

void ULetterInspectComponent::MoveLetterToInspectPoint()
{
    if (
        !IsValid(CurrentLetter) ||
        !IsValid(InspectPoint)
        )
    {
        return;
    }


    USceneComponent* Root =
        CurrentLetter->GetRootComponent();


    if (!IsValid(Root))
    {
        return;
    }


    // =========================================================
    // Detach
    // =========================================================

    CurrentLetter->DetachFromActor(
        FDetachmentTransformRules::
        KeepWorldTransform
    );


    // =========================================================
    // Attach
    // =========================================================

    CurrentLetter->AttachToComponent(
        InspectPoint,
        FAttachmentTransformRules::
        SnapToTargetNotIncludingScale
    );


    // =========================================================
    // Rotation
    // =========================================================

    Root->SetRelativeRotation(
        CurrentLetter
        ->InspectRotationOffset
    );


    // =========================================================
    // Location
    // =========================================================

    Root->SetRelativeLocation(
        CurrentLetter
        ->InspectLocationOffset
    );


    // =========================================================
    // Scale
    // =========================================================

    bool bScaleApplied =
        false;


    FVector FullSize =
        FVector::ZeroVector;


    if (
        CurrentLetter->bAutoNormalizeInspectSize &&
        CurrentLetter->GetActiveLetterMeshSize(
            FullSize
        )
        )
    {
        // Preserve the scale ratios that made the placed actor look correct.
        // Normalizing the raw mesh with a uniform relative scale would erase
        // any intentional non-uniform actor scale.
        const FVector OriginalWorldScale =
            OriginalLetterTransform.GetScale3D();


        const FVector AbsoluteOriginalScale(
            FMath::Abs(OriginalWorldScale.X),
            FMath::Abs(OriginalWorldScale.Y),
            FMath::Abs(OriginalWorldScale.Z)
        );


        const FVector PlacedMeshSize(
            FullSize.X * AbsoluteOriginalScale.X,
            FullSize.Y * AbsoluteOriginalScale.Y,
            FullSize.Z * AbsoluteOriginalScale.Z
        );


        const float MaxDimension =
            FMath::Max3(
                PlacedMeshSize.X,
                PlacedMeshSize.Y,
                PlacedMeshSize.Z
            );


        if (
            MaxDimension >
            KINDA_SMALL_NUMBER
            )
        {
            const float SafeTargetSize =
                FMath::Max(
                    CurrentLetter
                    ->InspectTargetSize,

                    1.0f
                );


            const float SafeMultiplier =
                FMath::Max(
                    CurrentLetter
                    ->InspectScaleMultiplier,

                    0.01f
                );


            float NormalizationFactor =
                SafeTargetSize /
                MaxDimension;


            NormalizationFactor *=
                SafeMultiplier;


            const FVector InspectWorldScale =
                OriginalWorldScale *
                NormalizationFactor;


            // Apply world scale after attachment so a scaled InspectPoint (or
            // one of its parents) cannot squash the inspected object.
            Root->SetWorldScale3D(
                InspectWorldScale
            );


            bScaleApplied =
                true;


            UE_LOG(
                LogTemp,
                Warning,
                TEXT(
                    "[LetterInspect] Auto Scale "
                    "Letter=%s "
                    "MeshSize=%.2f "
                    "TargetSize=%.2f "
                    "ScaleFactor=%.3f "
                    "WorldScale=%s"
                ),
                *CurrentLetter->GetName(),
                MaxDimension,
                SafeTargetSize,
                NormalizationFactor,
                *InspectWorldScale.ToString()
            );
        }
    }


    // ---------------------------------------------------------
    // Manual Scale
    // ---------------------------------------------------------

    if (!bScaleApplied)
    {
        if (
            !CurrentLetter
            ->bAutoNormalizeInspectSize
            )
        {
            Root->SetWorldScale3D(
                CurrentLetter
                ->ManualInspectScale
            );
        }
    }


    // =========================================================
    // Debug
    // =========================================================

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "[LetterInspect] Inspect Transform "
            "Letter=%s "
            "Location=%s "
            "Rotation=%s "
            "Scale=%s"
        ),
        *CurrentLetter->GetName(),

        *Root
        ->GetRelativeLocation()
        .ToString(),

        *Root
        ->GetRelativeRotation()
        .ToString(),

        *Root
        ->GetRelativeScale3D()
        .ToString()
    );
}


// =========================================================
// Restore Letter
// =========================================================

void ULetterInspectComponent::RestoreLetterState()
{
    if (!IsValid(CurrentLetter))
    {
        return;
    }


    CurrentLetter->DetachFromActor(
        FDetachmentTransformRules::
        KeepWorldTransform
    );


    if (IsValid(OriginalAttachParent))
    {
        CurrentLetter->AttachToComponent(
            OriginalAttachParent,
            FAttachmentTransformRules::
            KeepWorldTransform,
            OriginalAttachSocket
        );
    }


    CurrentLetter->SetActorTransform(
        OriginalLetterTransform,
        false,
        nullptr,
        ETeleportType::TeleportPhysics
    );


    if (IsValid(LetterPrimitive))
    {
        LetterPrimitive
            ->SetEnableGravity(
                bOriginalGravity
            );


        LetterPrimitive
            ->SetSimulatePhysics(
                bOriginalSimulatePhysics
            );
    }


    OriginalAttachParent =
        nullptr;


    OriginalAttachSocket =
        NAME_None;
}


// =========================================================
// Enable Depth Of Field
// =========================================================

void ULetterInspectComponent::EnableInspectDepthOfField()
{
    if (
        !IsValid(ViewCamera) ||
        !IsValid(InspectPoint)
        )
    {
        return;
    }


    OriginalPostProcessSettings =
        ViewCamera->PostProcessSettings;


    OriginalPostProcessBlendWeight =
        ViewCamera
        ->PostProcessBlendWeight;


    float FocusDistance =
        ManualFocusDistance;


    if (bAutoFocusOnInspectPoint)
    {
        FocusDistance =
            FVector::Distance(
                ViewCamera
                ->GetComponentLocation(),

                InspectPoint
                ->GetComponentLocation()
            );
    }


    ViewCamera
        ->PostProcessSettings
        .bOverride_DepthOfFieldFocalDistance =
        true;


    ViewCamera
        ->PostProcessSettings
        .DepthOfFieldFocalDistance =
        FocusDistance;


    ViewCamera
        ->PostProcessSettings
        .bOverride_DepthOfFieldFstop =
        true;


    ViewCamera
        ->PostProcessSettings
        .DepthOfFieldFstop =
        InspectFStop;


    ViewCamera
        ->PostProcessBlendWeight =
        1.0f;


    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "[LetterInspect] Focus Distance = %.2f"
        ),
        FocusDistance
    );
}


// =========================================================
// Restore Camera
// =========================================================

void ULetterInspectComponent::RestoreCameraPostProcess()
{
    if (!IsValid(ViewCamera))
    {
        return;
    }


    ViewCamera->PostProcessSettings =
        OriginalPostProcessSettings;


    ViewCamera->PostProcessBlendWeight =
        OriginalPostProcessBlendWeight;
}


// =========================================================
// Create Inspect Light
// =========================================================

void ULetterInspectComponent::CreateInspectLight()
{
    // ---------------------------------------------------------
    // Camera检查
    // ---------------------------------------------------------

    if (!IsValid(ViewCamera))
    {
        return;
    }


    // ---------------------------------------------------------
    // 已经存在
    // ---------------------------------------------------------

    if (IsValid(InspectLight))
    {
        return;
    }


    AActor* OwnerActor =
        GetOwner();


    if (!IsValid(OwnerActor))
    {
        return;
    }


    // =========================================================
    // Create Component
    // =========================================================

    InspectLight =
        NewObject<USpotLightComponent>(
            OwnerActor,
            USpotLightComponent::StaticClass(),
            TEXT("LetterInspectSoftLight")
        );


    if (!IsValid(InspectLight))
    {
        return;
    }


    // ---------------------------------------------------------
    // 告诉Actor这是它拥有的运行时Component
    // ---------------------------------------------------------

    OwnerActor->AddInstanceComponent(
        InspectLight
    );


    // ---------------------------------------------------------
    // Mobility
    // ---------------------------------------------------------

    InspectLight->SetMobility(
        EComponentMobility::Movable
    );


    // ---------------------------------------------------------
    // 注册
    // ---------------------------------------------------------

    InspectLight->RegisterComponent();


    // ---------------------------------------------------------
    // Attach Camera
    // ---------------------------------------------------------

    InspectLight->AttachToComponent(
        ViewCamera,
        FAttachmentTransformRules::
        SnapToTargetNotIncludingScale
    );


    // ---------------------------------------------------------
    // 默认关闭
    // ---------------------------------------------------------

    InspectLight->SetVisibility(
        false
    );


    // ---------------------------------------------------------
    // 设置初始参数
    // ---------------------------------------------------------

    UpdateInspectLight();


    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "[LetterInspect] Soft Inspect Light Created."
        )
    );
}


// =========================================================
// Update Inspect Light
// =========================================================

void ULetterInspectComponent::UpdateInspectLight()
{
    if (!IsValid(InspectLight))
    {
        return;
    }


    // =========================================================
    // Light Parameters
    // =========================================================

    InspectLight->SetIntensity(
        FMath::Max(
            InspectLightIntensity,
            0.0f
        )
    );


    InspectLight->SetAttenuationRadius(
        FMath::Max(
            InspectLightRadius,
            1.0f
        )
    );


    const float SafeOuterCone =
        FMath::Clamp(
            InspectLightOuterConeAngle,
            1.0f,
            89.0f
        );


    const float SafeInnerCone =
        FMath::Clamp(
            InspectLightInnerConeAngle,
            0.0f,
            SafeOuterCone
        );


    InspectLight->SetInnerConeAngle(
        SafeInnerCone
    );


    InspectLight->SetOuterConeAngle(
        SafeOuterCone
    );


    InspectLight->SetLightColor(
        InspectLightColor
    );


    InspectLight->SetCastShadows(
        bInspectLightCastShadows
    );


    // =========================================================
    // Position
    // =========================================================

    InspectLight->SetRelativeLocation(
        InspectLightLocalOffset
    );


    // =========================================================
    // Aim At Inspect Point
    // =========================================================

    if (
        bAutoAimInspectLight &&
        IsValid(InspectPoint)
        )
    {
        const FVector LightLocation =
            InspectLight
            ->GetComponentLocation();


        const FVector TargetLocation =
            InspectPoint
            ->GetComponentLocation();


        const FVector Direction =
            TargetLocation -
            LightLocation;


        if (!Direction.IsNearlyZero())
        {
            InspectLight->SetWorldRotation(
                Direction.Rotation()
            );
        }
    }
    else
    {
        // 如果关闭自动瞄准，
        // 默认和Camera方向一致。
        InspectLight->SetRelativeRotation(
            FRotator::ZeroRotator
        );
    }
}


// =========================================================
// Enable Inspect Light
// =========================================================

void ULetterInspectComponent::EnableInspectLight()
{
    if (!bEnableInspectLight)
    {
        return;
    }


    if (!IsValid(InspectLight))
    {
        CreateInspectLight();
    }


    if (!IsValid(InspectLight))
    {
        return;
    }


    // 每次打开时重新读取Details里的参数
    UpdateInspectLight();


    InspectLight->SetVisibility(
        true
    );


    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "[LetterInspect] Soft Inspect Light Enabled."
        )
    );
}


// =========================================================
// Disable Inspect Light
// =========================================================

void ULetterInspectComponent::DisableInspectLight()
{
    if (!IsValid(InspectLight))
    {
        return;
    }


    InspectLight->SetVisibility(
        false
    );
}


// =========================================================
// Create Description Widget
// =========================================================

void ULetterInspectComponent::CreateDescriptionWidget()
{
    if (
        !IsValid(PlayerController) ||
        !DescriptionWidgetClass ||
        !IsValid(CurrentLetter)
        )
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "[LetterInspect] Widget creation skipped."
            )
        );


        return;
    }


    ActiveWidget =
        CreateWidget<
        ULetterDescriptionWidget
        >(
            PlayerController,
            DescriptionWidgetClass
        );


    if (!IsValid(ActiveWidget))
    {
        return;
    }


    ActiveWidget
        ->ApplyLetterContent(
            CurrentLetter
            ->GetLetterTitle(),

            CurrentLetter
            ->GetLetterDescription()
        );


    ActiveWidget
        ->AddToViewport(
            WidgetZOrder
        );
}


// =========================================================
// Remove Description Widget
// =========================================================

void ULetterInspectComponent::RemoveDescriptionWidget()
{
    if (!IsValid(ActiveWidget))
    {
        return;
    }


    ActiveWidget
        ->RemoveFromParent();


    ActiveWidget =
        nullptr;
}


// =========================================================
// Project UI Presentation
// =========================================================

UObject* ULetterInspectComponent::GetOwnerObjectProperty(
    FName PropertyName
) const
{
    AActor* OwnerActor = GetOwner();


    if (!IsValid(OwnerActor) || PropertyName.IsNone())
    {
        return nullptr;
    }


    const FObjectPropertyBase* ObjectProperty =
        FindFProperty<FObjectPropertyBase>(
            OwnerActor->GetClass(),
            PropertyName
        );


    return ObjectProperty
        ? ObjectProperty->GetObjectPropertyValue_InContainer(OwnerActor)
        : nullptr;
}


void ULetterInspectComponent::HideMainProjectUI()
{
    if (!bHideMainHUDWhileInspecting)
    {
        return;
    }


    HiddenMainHUDWidget = Cast<UUserWidget>(
        GetOwnerObjectProperty(MainHUDWidgetPropertyName)
    );


    if (IsValid(HiddenMainHUDWidget))
    {
        OriginalMainHUDVisibility = static_cast<uint8>(
            HiddenMainHUDWidget->GetVisibility()
        );
        bMainHUDVisibilitySaved = true;


        HiddenMainHUDWidget->SetVisibility(
            ESlateVisibility::Collapsed
        );
    }


    HiddenWatchMenuPanel = Cast<USceneComponent>(
        GetOwnerObjectProperty(WatchMenuPanelPropertyName)
    );


    if (IsValid(HiddenWatchMenuPanel))
    {
        bOriginalWatchMenuVisible =
            HiddenWatchMenuPanel->IsVisible();
        bWatchMenuVisibilitySaved = true;


        HiddenWatchMenuPanel->SetVisibility(
            false,
            true
        );
    }


    UE_LOG(
        LogTemp,
        Log,
        TEXT(
            "[LetterInspect] Main UI hidden. HUD=%s WatchMenu=%s"
        ),
        IsValid(HiddenMainHUDWidget)
            ? *HiddenMainHUDWidget->GetName()
            : TEXT("NULL"),
        IsValid(HiddenWatchMenuPanel)
            ? *HiddenWatchMenuPanel->GetName()
            : TEXT("NULL")
    );
}


void ULetterInspectComponent::RestoreMainProjectUI()
{
    if (
        bMainHUDVisibilitySaved &&
        IsValid(HiddenMainHUDWidget)
        )
    {
        HiddenMainHUDWidget->SetVisibility(
            static_cast<ESlateVisibility>(
                OriginalMainHUDVisibility
            )
        );
    }


    if (
        bWatchMenuVisibilitySaved &&
        IsValid(HiddenWatchMenuPanel)
        )
    {
        HiddenWatchMenuPanel->SetVisibility(
            bOriginalWatchMenuVisible,
            true
        );
    }


    HiddenMainHUDWidget = nullptr;
    HiddenWatchMenuPanel = nullptr;
    bMainHUDVisibilitySaved = false;
    bWatchMenuVisibilitySaved = false;


    UE_LOG(
        LogTemp,
        Log,
        TEXT("[LetterInspect] Main UI restored.")
    );
}


// =========================================================
// Lock Player
// =========================================================

void ULetterInspectComponent::LockPlayerControl()
{
    if (!IsValid(PlayerController))
    {
        PlayerController =
            ResolvePlayerController();
    }


    if (!IsValid(PlayerController))
    {
        return;
    }


    LockedControlRotation =
        PlayerController->GetControlRotation();


    if (bLockMovementWhileInspecting)
    {
        PlayerController
            ->SetIgnoreMoveInput(true);
    }


    if (bLockLookWhileInspecting)
    {
        PlayerController
            ->SetIgnoreLookInput(true);
    }
}


// =========================================================
// Restore Player
// =========================================================

void ULetterInspectComponent::RestorePlayerControl()
{
    if (!IsValid(PlayerController))
    {
        return;
    }


    if (bLockMovementWhileInspecting)
    {
        PlayerController
            ->SetIgnoreMoveInput(false);
    }


    if (bLockLookWhileInspecting)
    {
        PlayerController
            ->SetIgnoreLookInput(false);
    }
}
