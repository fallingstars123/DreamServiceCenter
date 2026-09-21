#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InspectableLetter.generated.h"

class UStaticMeshComponent;
class USkeletalMeshComponent;
class UPrimitiveComponent;
class UStaticMesh;
class USkeletalMesh;
class UTexture2D;


UENUM(BlueprintType)
enum class EInspectableLetterMeshType : uint8
{
    StaticMesh UMETA(DisplayName = "Static Mesh"),
    SkeletalMesh UMETA(DisplayName = "Skeletal Mesh")
};


// =========================================================
// Inspectable Letter
// =========================================================

UCLASS()
class LETTERINSPECTION_API AInspectableLetter : public AActor
{
    GENERATED_BODY()

public:

    AInspectableLetter();


protected:

    virtual void BeginPlay() override;

    virtual void OnConstruction(
        const FTransform& Transform
    ) override;


public:

    // =========================================================
    // Mesh
    // =========================================================

    UPROPERTY(
        VisibleAnywhere,
        BlueprintReadOnly,
        Category = "Letter"
    )
    TObjectPtr<UStaticMeshComponent> LetterMesh;


    /**
     * Optional skeletal-mesh presentation.
     * Use SetSkeletalLetterMesh to activate it at runtime.
     */
    UPROPERTY(
        VisibleAnywhere,
        BlueprintReadOnly,
        Category = "Letter|Mesh"
    )
    TObjectPtr<USkeletalMeshComponent>
        SkeletalLetterMesh;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter|Mesh"
    )
    EInspectableLetterMeshType MeshType =
        EInspectableLetterMeshType::StaticMesh;


    UFUNCTION(
        BlueprintCallable,
        Category = "Letter|Mesh"
    )
    void SetStaticLetterMesh(
        UStaticMesh* InStaticMesh
    );


    UFUNCTION(
        BlueprintCallable,
        Category = "Letter|Mesh"
    )
    void SetSkeletalLetterMesh(
        USkeletalMesh* InSkeletalMesh
    );


    UFUNCTION(
        BlueprintCallable,
        Category = "Letter|Mesh"
    )
    void SetLetterMeshType(
        EInspectableLetterMeshType InMeshType
    );


    UFUNCTION(
        BlueprintPure,
        Category = "Letter|Mesh"
    )
    UPrimitiveComponent*
        GetActiveLetterPrimitive() const;


    UFUNCTION(
        BlueprintPure,
        Category = "Letter|Mesh"
    )
    bool GetActiveLetterMeshSize(
        FVector& OutSize
    ) const;


    // =========================================================
    // Letter Data
    // =========================================================

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter|Data",
        meta = (MultiLine = true)
    )
    FText LetterTitle;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter|Data",
        meta = (MultiLine = true)
    )
    FText LetterDescription;


    // =========================================================
    // Project Scanner Data (BPI_Scannable compatible)
    // =========================================================

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter|Scan"
    )
    TObjectPtr<UTexture2D> ScanObjectIcon = nullptr;


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter|Scan"
    )
    FText ScanObjectType = FText::FromString(TEXT("DOCUMENT"));


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter|Scan"
    )
    FText ScanStabilityImpact = FText::FromString(TEXT("LOW"));


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter|Scan"
    )
    FText ScanAnomalyLevel = FText::FromString(TEXT("NONE"));


    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter|Scan"
    )
    FText ScanSystemDirective = FText::FromString(TEXT("INSPECT"));


    /**
     * Signature intentionally matches /Game/Blueprints/BPI_Scannable.GetScanInfo.
     * BP_Astronaut's existing visor scanner can therefore read letter metadata.
     */
    UFUNCTION(
        BlueprintCallable,
        BlueprintNativeEvent,
        Category = "Letter|Scan"
    )
    void GetScanInfo(
        FText& ObjectName,
        UTexture2D*& ObjectIcon,
        FText& ObjectType,
        FText& StabilityImpact,
        FText& AnomalyLevel,
        FText& SystemDirective,
        FText& ObjectDescription
    );


    // =========================================================
    // Inspect Presentation
    // =========================================================

    /**
     * 进入观察模式以后，
     * 相对于 InspectPoint 的旋转。
     *
     * 这个参数和物体在世界里的朝向完全无关。
     *
     * 示例：
     *
     * 普通信件：
     * 0 / 0 / 0
     *
     * 如果进入观察以后横着：
     * Roll = 90
     *
     * 如果背面朝向玩家：
     * Yaw = 180
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter|Inspect"
    )
    FRotator InspectRotationOffset =
        FRotator::ZeroRotator;


    /**
     * 进入观察模式后的局部位置偏移。
     *
     * 用于：
     *
     * 模型Pivot不居中
     * 某些模型需要稍微向左/右/上/下移动
     *
     * X：前后
     * Y：左右
     * Z：上下
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter|Inspect"
    )
    FVector InspectLocationOffset =
        FVector::ZeroVector;


    /**
     * 是否根据Static Mesh尺寸自动计算观察Scale。
     *
     * 开启以后：
     *
     * 很小的物体会自动放大。
     * 很大的物体会自动缩小。
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter|Inspect"
    )
    bool bAutoNormalizeInspectSize = true;


    /**
     * 自动尺寸模式下，
     * 希望模型最长边最终大约是多少厘米。
     *
     * 建议：
     *
     * 30 ~ 50
     *
     * 先从35开始。
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter|Inspect",
        meta = (
            EditCondition = "bAutoNormalizeInspectSize",
            EditConditionHides,
            ClampMin = "1.0",
            UIMin = "1.0"
            )
    )
    float InspectTargetSize = 35.0f;


    /**
     * 自动计算尺寸以后再乘一个倍率。
     *
     * 1.0 = 默认
     * 0.8 = 小20%
     * 1.2 = 大20%
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter|Inspect",
        meta = (
            EditCondition = "bAutoNormalizeInspectSize",
            EditConditionHides,
            ClampMin = "0.01",
            UIMin = "0.01"
            )
    )
    float InspectScaleMultiplier = 1.0f;


    /**
     * 如果关闭自动尺寸，
     * 就使用这里的世界Scale。
     * 该数值不会再被InspectPoint父级Scale二次挤压。
     */
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Letter|Inspect",
        meta = (
            EditCondition = "!bAutoNormalizeInspectSize",
            EditConditionHides
            )
    )
    FVector ManualInspectScale =
        FVector(1.0f, 1.0f, 1.0f);


    // =========================================================
    // Getters
    // =========================================================

    UFUNCTION(
        BlueprintPure,
        Category = "Letter|Data"
    )
    FText GetLetterTitle() const
    {
        return LetterTitle;
    }


    UFUNCTION(
        BlueprintPure,
        Category = "Letter|Data"
    )
    FText GetLetterDescription() const
    {
        return LetterDescription;
    }


private:

    void RefreshMeshPresentation();

    void EnsureProjectScannableInterface();
};
