#include "VisorScannableActor.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/Texture2D.h"
#include "UObject/Class.h"
#include "UObject/UnrealType.h"
#include "UObject/UObjectGlobals.h"

namespace VisorScannableActorNames
{
    static const FName GetScanInfo(TEXT("GetScanInfo"));

    FString NormalizeParameterName(FString ParameterName)
    {
        ParameterName.RemoveFromStart(TEXT("Out"), ESearchCase::IgnoreCase);
        ParameterName.ReplaceInline(TEXT("_"), TEXT(""));
        ParameterName.ReplaceInline(TEXT(" "), TEXT(""));
        return ParameterName.ToLower();
    }
}

AVisorScannableActor::AVisorScannableActor()
{
    PrimaryActorTick.bCanEverTick = false;

    ScanMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScanMesh"));
    SetRootComponent(ScanMesh);
    ScanMesh->SetMobility(EComponentMobility::Static);
}

void AVisorScannableActor::ProcessEvent(
    UFunction* Function,
    void* Parameters
)
{
    if (
        Function &&
        Function->GetFName() == VisorScannableActorNames::GetScanInfo &&
        FillScanInfoParameters(Function, Parameters)
        )
    {
        UE_LOG(
            LogTemp,
            Log,
            TEXT("[VisorScannable] Supplied scan info for %s."),
            *GetNameSafe(this)
        );
        return;
    }

    Super::ProcessEvent(Function, Parameters);
}

void AVisorScannableActor::BeginPlay()
{
    Super::BeginPlay();
    EnsureProjectScannableInterface();
    RefreshTraceCollision();
}

void AVisorScannableActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    EnsureProjectScannableInterface();
    RefreshTraceCollision();
}

void AVisorScannableActor::EnsureProjectScannableInterface()
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

    // BPI_Scannable belongs to project content and cannot be a native base
    // interface of this reusable plugin module. Register it after it is loaded.
    RuntimeClass->Interfaces.Emplace(ScannableInterface, 0, true);

    UE_LOG(
        LogTemp,
        Log,
        TEXT("[VisorScannable] Registered %s as BPI_Scannable."),
        *RuntimeClass->GetName()
    );
}

void AVisorScannableActor::RefreshTraceCollision()
{
    if (!bForceVisibilityTraceCollision || !IsValid(ScanMesh))
    {
        return;
    }

    if (ScanMesh->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
    {
        ScanMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }

    ScanMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AVisorScannableActor::GetScanInfo_Implementation(
    FText& OutObjectName,
    UTexture2D*& OutObjectIcon,
    FText& OutObjectType,
    FText& OutStabilityImpact,
    FText& OutAnomalyLevel,
    FText& OutSystemDirective,
    FText& OutObjectDescription
)
{
    OutObjectName = ObjectName;
    OutObjectIcon = ObjectIcon;
    OutObjectType = ObjectType;
    OutStabilityImpact = StabilityImpact;
    OutAnomalyLevel = AnomalyLevel;
    OutSystemDirective = SystemDirective;
    OutObjectDescription = ObjectDescription;
}

bool AVisorScannableActor::FillScanInfoParameters(
    UFunction* Function,
    void* Parameters
) const
{
    if (!Function || !Parameters)
    {
        return false;
    }

    int32 FilledParameterCount = 0;

    for (TFieldIterator<FProperty> It(Function); It; ++It)
    {
        FProperty* Property = *It;
        if (!Property->HasAnyPropertyFlags(CPF_Parm))
        {
            continue;
        }

        const FString ParameterName =
            VisorScannableActorNames::NormalizeParameterName(
                Property->GetName()
            );

        if (FTextProperty* TextProperty = CastField<FTextProperty>(Property))
        {
            const FText* SourceText = nullptr;

            if (ParameterName == TEXT("objectname"))
            {
                SourceText = &ObjectName;
            }
            else if (ParameterName == TEXT("objecttype"))
            {
                SourceText = &ObjectType;
            }
            else if (ParameterName == TEXT("stabilityimpact"))
            {
                SourceText = &StabilityImpact;
            }
            else if (ParameterName == TEXT("anomalylevel"))
            {
                SourceText = &AnomalyLevel;
            }
            else if (ParameterName == TEXT("systemdirective"))
            {
                SourceText = &SystemDirective;
            }
            else if (ParameterName == TEXT("objectdescription"))
            {
                SourceText = &ObjectDescription;
            }

            if (SourceText)
            {
                TextProperty->SetPropertyValue_InContainer(
                    Parameters,
                    *SourceText
                );
                ++FilledParameterCount;
            }
        }
        else if (
            ParameterName == TEXT("objecticon") &&
            CastField<FObjectPropertyBase>(Property)
            )
        {
            FObjectPropertyBase* ObjectProperty =
                CastFieldChecked<FObjectPropertyBase>(Property);
            ObjectProperty->SetObjectPropertyValue_InContainer(
                Parameters,
                ObjectIcon
            );
            ++FilledParameterCount;
        }
    }

    return FilledParameterCount == 7;
}
