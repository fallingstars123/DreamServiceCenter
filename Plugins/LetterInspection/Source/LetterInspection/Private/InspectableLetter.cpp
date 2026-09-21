#include "InspectableLetter.h"

#include "Components/PrimitiveComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture2D.h"
#include "UObject/Class.h"
#include "UObject/UObjectGlobals.h"


// =========================================================
// Constructor
// =========================================================

AInspectableLetter::AInspectableLetter()
{
    PrimaryActorTick.bCanEverTick = false;


    LetterMesh =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("LetterMesh")
        );


    SetRootComponent(
        LetterMesh
    );


    LetterMesh->SetMobility(
        EComponentMobility::Movable
    );


    SkeletalLetterMesh =
        CreateDefaultSubobject<USkeletalMeshComponent>(
            TEXT("SkeletalLetterMesh")
        );


    SkeletalLetterMesh->SetupAttachment(
        LetterMesh
    );


    SkeletalLetterMesh->SetMobility(
        EComponentMobility::Movable
    );


    RefreshMeshPresentation();
}


// =========================================================
// Begin Play
// =========================================================

void AInspectableLetter::BeginPlay()
{
    Super::BeginPlay();

    EnsureProjectScannableInterface();
    RefreshMeshPresentation();
}


// =========================================================
// Construction
// =========================================================

void AInspectableLetter::OnConstruction(
    const FTransform& Transform
)
{
    Super::OnConstruction(Transform);

    EnsureProjectScannableInterface();
    RefreshMeshPresentation();
}


// =========================================================
// Project Scanner Compatibility
// =========================================================

void AInspectableLetter::EnsureProjectScannableInterface()
{
    static TWeakObjectPtr<UClass> CachedScannableInterface;


    UClass* ScannableInterface = CachedScannableInterface.Get();


    if (!IsValid(ScannableInterface))
    {
        ScannableInterface = LoadClass<UInterface>(
            nullptr,
            TEXT("/Game/Blueprints/BPI_Scannable.BPI_Scannable_C")
        );


        CachedScannableInterface = ScannableInterface;
    }


    UClass* RuntimeClass = GetClass();


    if (
        !IsValid(ScannableInterface) ||
        !IsValid(RuntimeClass) ||
        RuntimeClass->ImplementsInterface(ScannableInterface)
        )
    {
        return;
    }


    // BPI_Scannable is project content, so the reusable runtime module cannot
    // inherit it at C++ compile time. Register it on the generated actor class
    // after the interface asset is available. The native GetScanInfo function
    // below supplies the exact output signature used by BP_Astronaut.
    RuntimeClass->Interfaces.Emplace(
        ScannableInterface,
        0,
        true
    );


    UE_LOG(
        LogTemp,
        Log,
        TEXT("[LetterInspect] Registered %s as BPI_Scannable."),
        *RuntimeClass->GetName()
    );
}


void AInspectableLetter::GetScanInfo_Implementation(
    FText& ObjectName,
    UTexture2D*& ObjectIcon,
    FText& ObjectType,
    FText& StabilityImpact,
    FText& AnomalyLevel,
    FText& SystemDirective,
    FText& ObjectDescription
)
{
    ObjectName = LetterTitle;
    ObjectIcon = ScanObjectIcon;
    ObjectType = ScanObjectType;
    StabilityImpact = ScanStabilityImpact;
    AnomalyLevel = ScanAnomalyLevel;
    SystemDirective = ScanSystemDirective;
    ObjectDescription = LetterDescription;
}


// =========================================================
// Mesh API
// =========================================================

void AInspectableLetter::SetStaticLetterMesh(
    UStaticMesh* InStaticMesh
)
{
    if (IsValid(LetterMesh))
    {
        LetterMesh->SetStaticMesh(InStaticMesh);
    }

    if (IsValid(SkeletalLetterMesh))
    {
        SkeletalLetterMesh->SetSkeletalMesh(nullptr);
    }

    MeshType =
        EInspectableLetterMeshType::StaticMesh;

    RefreshMeshPresentation();
}


void AInspectableLetter::SetSkeletalLetterMesh(
    USkeletalMesh* InSkeletalMesh
)
{
    if (IsValid(SkeletalLetterMesh))
    {
        SkeletalLetterMesh->SetSkeletalMesh(
            InSkeletalMesh
        );
    }

    if (IsValid(LetterMesh))
    {
        LetterMesh->SetStaticMesh(nullptr);
    }

    MeshType =
        EInspectableLetterMeshType::SkeletalMesh;

    RefreshMeshPresentation();
}


void AInspectableLetter::SetLetterMeshType(
    EInspectableLetterMeshType InMeshType
)
{
    MeshType = InMeshType;

    RefreshMeshPresentation();
}


UPrimitiveComponent*
AInspectableLetter::GetActiveLetterPrimitive() const
{
    if (
        MeshType ==
        EInspectableLetterMeshType::SkeletalMesh
        )
    {
        return SkeletalLetterMesh;
    }

    return LetterMesh;
}


bool AInspectableLetter::GetActiveLetterMeshSize(
    FVector& OutSize
) const
{
    OutSize = FVector::ZeroVector;

    if (
        MeshType ==
        EInspectableLetterMeshType::SkeletalMesh
        )
    {
        if (!IsValid(SkeletalLetterMesh))
        {
            return false;
        }

        const USkeletalMesh* SkeletalMesh =
            SkeletalLetterMesh
            ->GetSkeletalMeshAsset();

        if (!IsValid(SkeletalMesh))
        {
            return false;
        }

        OutSize =
            SkeletalMesh
            ->GetBounds()
            .BoxExtent *
            2.0f;

        return !OutSize.IsNearlyZero();
    }

    if (!IsValid(LetterMesh))
    {
        return false;
    }

    const UStaticMesh* StaticMesh =
        LetterMesh->GetStaticMesh();

    if (!IsValid(StaticMesh))
    {
        return false;
    }

    OutSize =
        StaticMesh
        ->GetBounds()
        .BoxExtent *
        2.0f;

    return !OutSize.IsNearlyZero();
}


void AInspectableLetter::RefreshMeshPresentation()
{
    const bool bUseSkeletalMesh =
        MeshType ==
        EInspectableLetterMeshType::SkeletalMesh;

    if (IsValid(LetterMesh))
    {
        LetterMesh->SetVisibility(
            !bUseSkeletalMesh,
            true
        );

        LetterMesh->SetHiddenInGame(
            bUseSkeletalMesh,
            true
        );
    }

    if (IsValid(SkeletalLetterMesh))
    {
        SkeletalLetterMesh->SetVisibility(
            bUseSkeletalMesh,
            true
        );

        SkeletalLetterMesh->SetHiddenInGame(
            !bUseSkeletalMesh,
            true
        );
    }


    // The scan component traces on Visibility by default. Keep the active
    // inspectable mesh queryable even when a source asset shipped as NoCollision.
    UPrimitiveComponent* ActivePrimitive =
        GetActiveLetterPrimitive();


    if (IsValid(ActivePrimitive))
    {
        if (
            ActivePrimitive->GetCollisionEnabled() ==
            ECollisionEnabled::NoCollision
            )
        {
            ActivePrimitive->SetCollisionEnabled(
                ECollisionEnabled::QueryOnly
            );
        }


        ActivePrimitive->SetCollisionResponseToChannel(
            ECC_Visibility,
            ECR_Block
        );
    }
}
