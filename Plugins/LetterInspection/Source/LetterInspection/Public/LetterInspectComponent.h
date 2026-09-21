#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/Scene.h"
#include "InputCoreTypes.h"

#include "LetterInspectComponent.generated.h"


class UCameraComponent;
class USceneComponent;
class UPrimitiveComponent;
class USpotLightComponent;
class UUserWidget;

class AInspectableLetter;
class APlayerController;

class ULetterDescriptionWidget;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnLetterScanModeChanged,
    bool,
    bIsActive
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnLetterScanTargetChanged,
    AInspectableLetter*,
    NewTarget,
    AInspectableLetter*,
    PreviousTarget
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnLetterScanProgressChanged,
    AInspectableLetter*,
    Target,
    float,
    NormalizedProgress
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnLetterScanCompleted,
    AInspectableLetter*,
    Target
);


// =========================================================
// Letter Inspect Component
// =========================================================

UCLASS(
    ClassGroup = (Interaction),
    meta = (BlueprintSpawnableComponent)
)
class LETTERINSPECTION_API ULetterInspectComponent : public UActorComponent
{
    GENERATED_BODY()


public:

    ULetterInspectComponent();


protected:

    virtual void BeginPlay() override;

    virtual void EndPlay(
        const EEndPlayReason::Type EndPlayReason
    ) override;

    virtual void TickComponent(
        float DeltaTime,
        ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction
    ) override;


public:

    // =========================================================
    // Setup
    // =========================================================

    /**
     * Character BeginPlay调用一次。
     *
     * InCamera：
     * 玩家实际使用Camera。
     *
     * InInspectPoint：
     * Camera下面的Scene Component。
     */
    UFUNCTION(
        BlueprintCallable,
        Category = "Letter Inspect|Setup"
    )
    void InitializeInspectSystem(
        UCameraComponent* InCamera,
        USceneComponent* InInspectPoint
    );


    UFUNCTION(
        BlueprintPure,
        Category = "Letter Inspect|Setup"
    )
    bool IsInitialized() const;


    /** 供自动启动器和蓝图安全地补做一次相机/InspectPoint初始化。 */
    UFUNCTION(
        BlueprintCallable,
        Category = "Letter Inspect|Setup"
    )
    void EnsureAutoInitialized();


    // =========================================================
    // Inspect
    // =========================================================

    UFUNCTION(
        BlueprintCallable,
        Category = "Letter Inspect"
    )
    bool BeginInspect(
        AInspectableLetter* Letter
    );


    UFUNCTION(
        BlueprintCallable,
        Category = "Letter Inspect"
    )
    void EndInspect();


    UFUNCTION(
        BlueprintPure,
        Category = "Letter Inspect"
    )
    bool IsInspecting() const
    {
        return bIsInspecting;
    }


    UFUNCTION(
        BlueprintPure,
        Category = "Letter Inspect"
    )
    AInspectableLetter* GetCurrentLetter() const
    {
        return CurrentLetter;
    }


    // =========================================================
    // Scan
    // =========================================================

    /** 开启/关闭扫描模式。可直接接 BP_Astronaut 现有的扫描模式状态。 */
    UFUNCTION(
        BlueprintCallable,
        Category = "Letter Inspect|Scan"
    )
    void SetScanModeActive(bool bActive);


    /** 适合直接接键盘 F Pressed。 */
    UFUNCTION(
        BlueprintCallable,
        Category = "Letter Inspect|Scan"
    )
    void ToggleScanMode();


    /** 适合接鼠标左键 Pressed/Released。 */
    UFUNCTION(
        BlueprintCallable,
        Category = "Letter Inspect|Scan"
    )
    void SetScanInputHeld(bool bHeld);


    UFUNCTION(
        BlueprintPure,
        Category = "Letter Inspect|Scan"
    )
    bool IsLetterScanModeActive() const
    {
        return bScanModeActive;
    }


    UFUNCTION(
        BlueprintPure,
        Category = "Letter Inspect|Scan"
    )
    AInspectableLetter* GetScanTarget() const
    {
        return ScanTarget;
    }


    UFUNCTION(
        BlueprintPure,
        Category = "Letter Inspect|Scan"
    )
    float GetScanProgress() const
    {
        return ScanProgress;
    }


    /** 自动从角色查找启用中的 Camera，并创建镜头前的 InspectPoint。 */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Setup"
    )
    bool bAutoInitializeFromOwner = true;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Setup",
        meta = (EditCondition = "bAutoInitializeFromOwner")
    )
    FVector AutoInspectPointOffset = FVector(80.0f, 0.0f, 0.0f);


    /**
     * 无需改输入图：组件会同步监听 F 和鼠标左键。
     * 如果已在蓝图调用 SetScanModeActive/SetScanInputHeld，可关闭此项。
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Scan|Input"
    )
    bool bUseDefaultScanInput = true;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Scan|Input",
        meta = (EditCondition = "bUseDefaultScanInput")
    )
    FKey ScanToggleKey;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Scan|Input",
        meta = (EditCondition = "bUseDefaultScanInput")
    )
    FKey ScanHoldKey;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Scan|Input",
        meta = (EditCondition = "bUseDefaultScanInput")
    )
    FKey InspectExitKey;


    /** PIE里Esc会停止运行，所以同时提供右键作为退出。F也可退出。 */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Scan|Input",
        meta = (EditCondition = "bUseDefaultScanInput")
    )
    FKey InspectSecondaryExitKey;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Scan",
        meta = (ClampMin = "1.0", Units = "cm")
    )
    float ScanDistance = 800.0f;


    /** 使用小球检测而不是单像素射线，第一人称瞄准更稳定。 */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Scan",
        meta = (ClampMin = "0.0", Units = "cm")
    )
    float ScanRadius = 8.0f;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Scan"
    )
    TEnumAsByte<ECollisionChannel> ScanTraceChannel = ECC_Visibility;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Scan",
        meta = (ClampMin = "0.01", Units = "s")
    )
    float ScanDuration = 0.45f;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Scan",
        meta = (ClampMin = "0.0", Units = "s")
    )
    float ScanTargetGracePeriod = 0.12f;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Scan",
        meta = (ClampMin = "0.0")
    )
    float ScanProgressDecayPerSecond = 2.5f;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Scan"
    )
    bool bAutoBeginInspectOnScanComplete = true;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Scan|Highlight"
    )
    bool bHighlightScanTarget = true;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Scan|Highlight",
        meta = (EditCondition = "bHighlightScanTarget", ClampMin = "0", ClampMax = "255")
    )
    int32 ScanCustomDepthStencilValue = 252;


    UPROPERTY(BlueprintAssignable, Category = "Letter Inspect|Scan")
    FOnLetterScanModeChanged OnScanModeChanged;

    UPROPERTY(BlueprintAssignable, Category = "Letter Inspect|Scan")
    FOnLetterScanTargetChanged OnScanTargetChanged;

    UPROPERTY(BlueprintAssignable, Category = "Letter Inspect|Scan")
    FOnLetterScanProgressChanged OnScanProgressChanged;

    UPROPERTY(BlueprintAssignable, Category = "Letter Inspect|Scan")
    FOnLetterScanCompleted OnScanCompleted;


    // =========================================================
    // Widget
    // =========================================================

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|UI"
    )
    TSubclassOf<ULetterDescriptionWidget>
        DescriptionWidgetClass;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|UI"
    )
    int32 WidgetZOrder = 50;


    /** 查看物体时隐藏 BP_Astronaut 的主HUD和手表菜单。 */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|UI"
    )
    bool bHideMainHUDWhileInspecting = true;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|UI",
        meta = (EditCondition = "bHideMainHUDWhileInspecting")
    )
    FName MainHUDWidgetPropertyName = TEXT("VisorHUDWidget");


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|UI",
        meta = (EditCondition = "bHideMainHUDWhileInspecting")
    )
    FName WatchMenuPanelPropertyName = TEXT("WatchMenuPanel");


    // =========================================================
    // Camera / DOF
    // =========================================================

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Camera"
    )
    float InspectFStop = 1.2f;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Camera"
    )
    bool bAutoFocusOnInspectPoint = true;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Camera"
    )
    float ManualFocusDistance = 80.0f;


    // =========================================================
    // Inspect Light
    // =========================================================

    /**
     * 阅读物体时是否开启柔和聚光灯。
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Light"
    )
    bool bEnableInspectLight = true;


    /**
     * 聚光灯强度。
     *
     * 默认故意设置得不高，
     * 避免把白纸直接打爆。
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Light",
        meta = (
            EditCondition = "bEnableInspectLight",
            ClampMin = "0.0"
            )
    )
    float InspectLightIntensity = 1200.0f;


    /**
     * 光线有效范围。
     *
     * UE单位：cm
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Light",
        meta = (
            EditCondition = "bEnableInspectLight",
            ClampMin = "1.0"
            )
    )
    float InspectLightRadius = 280.0f;


    /**
     * 聚光灯内锥角。
     *
     * 数值大一些会更柔和。
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Light",
        meta = (
            EditCondition = "bEnableInspectLight",
            ClampMin = "0.0",
            ClampMax = "89.0"
            )
    )
    float InspectLightInnerConeAngle = 24.0f;


    /**
     * 聚光灯外锥角。
     *
     * 48度不会产生特别明显的小光圈。
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Light",
        meta = (
            EditCondition = "bEnableInspectLight",
            ClampMin = "1.0",
            ClampMax = "89.0"
            )
    )
    float InspectLightOuterConeAngle = 48.0f;


    /**
     * 聚光灯颜色。
     *
     * 默认略微偏暖，
     * 接近阅读灯。
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Light",
        meta = (
            EditCondition = "bEnableInspectLight"
            )
    )
    FLinearColor InspectLightColor =
        FLinearColor(
            1.0f,
            0.90f,
            0.78f,
            1.0f
        );


    /**
     * 灯相对于Camera的位置。
     *
     * 默认：
     *
     * 稍微向左
     * 稍微向上
     *
     * 这样不会完全正面平打，
     * 物体会有一点立体感。
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Light",
        meta = (
            EditCondition = "bEnableInspectLight"
            )
    )
    FVector InspectLightLocalOffset =
        FVector(
            5.0f,
            -10.0f,
            8.0f
        );


    /**
     * 是否自动让SpotLight朝向InspectPoint。
     *
     * 推荐保持开启。
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Light"
    )
    bool bAutoAimInspectLight = true;


    /**
     * 是否投射阴影。
     *
     * 默认关闭：
     *
     * 更柔和
     * 性能更低
     * 不容易产生硬阴影
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Light"
    )
    bool bInspectLightCastShadows = false;


    // =========================================================
    // Player Control
    // =========================================================

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Player"
    )
    bool bLockMovementWhileInspecting = true;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Player"
    )
    bool bLockLookWhileInspecting = true;


    /** 每帧固定Control Rotation，防止自定义Aim逻辑绕过Ignore Look Input。 */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter Inspect|Player"
    )
    bool bHardLockViewRotation = true;


private:

    // =========================================================
    // References
    // =========================================================

    UPROPERTY(Transient)
    TObjectPtr<UCameraComponent>
        ViewCamera = nullptr;


    UPROPERTY(Transient)
    TObjectPtr<USceneComponent>
        InspectPoint = nullptr;


    UPROPERTY(Transient)
    TObjectPtr<AInspectableLetter>
        CurrentLetter = nullptr;


    UPROPERTY(Transient)
    TObjectPtr<ULetterDescriptionWidget>
        ActiveWidget = nullptr;


    UPROPERTY(Transient)
    TObjectPtr<APlayerController>
        PlayerController = nullptr;


    /**
     * 运行时创建的阅读聚光灯。
     */
    UPROPERTY(Transient)
    TObjectPtr<USpotLightComponent>
        InspectLight = nullptr;


    UPROPERTY(Transient)
    TObjectPtr<USceneComponent>
        AutoInspectPoint = nullptr;


    UPROPERTY(Transient)
    TObjectPtr<AInspectableLetter>
        ScanTarget = nullptr;


    UPROPERTY(Transient)
    TObjectPtr<UPrimitiveComponent>
        HighlightedPrimitive = nullptr;


    UPROPERTY(Transient)
    TObjectPtr<UUserWidget>
        HiddenMainHUDWidget = nullptr;


    UPROPERTY(Transient)
    TObjectPtr<USceneComponent>
        HiddenWatchMenuPanel = nullptr;


    // =========================================================
    // State
    // =========================================================

    bool bIsInspecting = false;

    bool bScanModeActive = false;

    bool bScanInputHeld = false;

    bool bScanCompletedForCurrentTarget = false;

    bool bOriginalRenderCustomDepth = false;

    int32 OriginalCustomDepthStencilValue = 0;

    float ScanProgress = 0.0f;

    float ScanTargetLostTime = 0.0f;

    bool bMainHUDVisibilitySaved = false;

    bool bWatchMenuVisibilitySaved = false;

    uint8 OriginalMainHUDVisibility = 0;

    bool bOriginalWatchMenuVisible = false;

    FRotator LockedControlRotation = FRotator::ZeroRotator;


    // =========================================================
    // Original Letter State
    // =========================================================

    FTransform OriginalLetterTransform;


    UPROPERTY(Transient)
    TObjectPtr<USceneComponent>
        OriginalAttachParent = nullptr;


    FName OriginalAttachSocket =
        NAME_None;


    UPROPERTY(Transient)
    TObjectPtr<UPrimitiveComponent>
        LetterPrimitive = nullptr;


    bool bOriginalSimulatePhysics = false;

    bool bOriginalGravity = false;


    // =========================================================
    // Camera Original State
    // =========================================================

    FPostProcessSettings
        OriginalPostProcessSettings;


    float OriginalPostProcessBlendWeight =
        0.0f;


private:

    // =========================================================
    // Internal Functions
    // =========================================================

    APlayerController*
        ResolvePlayerController();


    UPrimitiveComponent*
        FindLetterPrimitive(
            AInspectableLetter* Letter
        ) const;


    void AutoInitializeInspectSystem();

    void PollDefaultScanInput();

    void UpdateLetterScan(float DeltaTime);

    AInspectableLetter* TraceForInspectableLetter() const;

    AInspectableLetter* ResolveInspectableLetter(AActor* HitActor) const;

    void SetScanTargetInternal(AInspectableLetter* NewTarget);

    void ApplyScanHighlight(AInspectableLetter* Target);

    void RestoreScanHighlight();

    void ResetScanProgress();


    // ---------------------------------------------------------
    // Letter
    // ---------------------------------------------------------

    void SaveLetterState();

    void MoveLetterToInspectPoint();

    void RestoreLetterState();


    // ---------------------------------------------------------
    // Camera
    // ---------------------------------------------------------

    void EnableInspectDepthOfField();

    void RestoreCameraPostProcess();


    // ---------------------------------------------------------
    // Inspect Light
    // ---------------------------------------------------------

    void CreateInspectLight();

    void UpdateInspectLight();

    void EnableInspectLight();

    void DisableInspectLight();


    // ---------------------------------------------------------
    // UI
    // ---------------------------------------------------------

    void CreateDescriptionWidget();

    void RemoveDescriptionWidget();

    void HideMainProjectUI();

    void RestoreMainProjectUI();

    UObject* GetOwnerObjectProperty(FName PropertyName) const;


    // ---------------------------------------------------------
    // Player
    // ---------------------------------------------------------

    void LockPlayerControl();

    void RestorePlayerControl();
};
