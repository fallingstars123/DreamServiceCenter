#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VisorScannableActor.generated.h"

class UStaticMeshComponent;
class UTexture2D;

/**
 * Generic object for BP_Astronaut's existing visor scanner.
 *
 * This deliberately does not inherit AInspectableLetter, so scanning it drives
 * WBP_VisorHUD without starting the LetterInspection close-up presentation.
 */
UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Visor Scannable Actor"))
class LETTERINSPECTION_API AVisorScannableActor : public AActor
{
    GENERATED_BODY()

public:
    AVisorScannableActor();

    /**
     * BPI_Scannable is a project Blueprint interface that is attached at
     * runtime. Intercept its message call so Blueprint-interface parameter
     * memory is populated even when UE does not route it through the inherited
     * native BlueprintNativeEvent on a generated child class.
     */
    virtual void ProcessEvent(UFunction* Function, void* Parameters) override;

protected:
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scannable")
    TObjectPtr<UStaticMeshComponent> ScanMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scannable|Information")
    FText ObjectName = FText::FromString(TEXT("SCANNABLE OBJECT"));

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scannable|Information")
    TObjectPtr<UTexture2D> ObjectIcon = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scannable|Information")
    FText ObjectType = FText::FromString(TEXT("DREAM INFRASTRUCTURE"));

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scannable|Information")
    FText StabilityImpact = FText::FromString(TEXT("LOW"));

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scannable|Information")
    FText AnomalyLevel = FText::FromString(TEXT("NORMAL"));

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scannable|Information")
    FText SystemDirective = FText::FromString(TEXT("NO ACTION REQUIRED"));

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "Scannable|Information",
        meta = (MultiLine = true)
    )
    FText ObjectDescription = FText::FromString(
        TEXT("Describe this object for the visor scan panel.")
    );

    /** Keep the mesh traceable by the player's Visibility line trace. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scannable|Collision")
    bool bForceVisibilityTraceCollision = true;

    /** Exact signature consumed by /Game/Blueprints/BPI_Scannable. */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Scannable")
    void GetScanInfo(
        FText& OutObjectName,
        UTexture2D*& OutObjectIcon,
        FText& OutObjectType,
        FText& OutStabilityImpact,
        FText& OutAnomalyLevel,
        FText& OutSystemDirective,
        FText& OutObjectDescription
    );

private:
    void EnsureProjectScannableInterface();
    void RefreshTraceCollision();
    bool FillScanInfoParameters(UFunction* Function, void* Parameters) const;
};
