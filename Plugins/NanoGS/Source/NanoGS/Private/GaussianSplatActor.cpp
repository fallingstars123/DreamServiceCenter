// Copyright Epic Games, Inc. All Rights Reserved.

#include "GaussianSplatActor.h"
#include "GaussianSplatComponent.h"
#include "GaussianSplatAsset.h"
#include "UObject/UObjectGlobals.h"

AGaussianSplatActor::AGaussianSplatActor()
{
	// Create the Gaussian Splat component as a default subobject
	GaussianSplatComponent = CreateDefaultSubobject<UGaussianSplatComponent>(TEXT("GaussianSplatComponent"));
	RootComponent = GaussianSplatComponent;
}

void AGaussianSplatActor::PostLoad()
{
	Super::PostLoad();
	RemoveInvalidSelectionBoxes();

	auto PrepareLoadedBoxes = [](TArray<TObjectPtr<UGaussianSplatSelectionBoxComponent>>& Boxes,
		EGaussianSplatSelectionBoxMode Mode)
	{
		for (int32 Index = 0; Index < Boxes.Num(); ++Index)
		{
			UGaussianSplatSelectionBoxComponent* Box = Boxes[Index];
			if (!IsValid(Box))
			{
				continue;
			}
			Box->SelectionMode = Mode;
			Box->ShapeColor = Mode == EGaussianSplatSelectionBoxMode::Keep
				? FColor(40, 220, 80)
				: FColor(220, 55, 55);
			Box->SelectionBoxTransform = Box->GetRelativeTransform();
			if (Box->SelectionBoxName.IsNone())
			{
				Box->SelectionBoxName = FName(*FString::Printf(
					TEXT("%s Box %d"),
					Mode == EGaussianSplatSelectionBoxMode::Keep ? TEXT("Keep") : TEXT("Cull"),
					Index + 1));
			}
		}
	};

	PrepareLoadedBoxes(CullSelectionBoxes, EGaussianSplatSelectionBoxMode::Cull);
	PrepareLoadedBoxes(KeepSelectionBoxes, EGaussianSplatSelectionBoxMode::Keep);
}

#if WITH_EDITOR
void AGaussianSplatActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.GetPropertyName();
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AGaussianSplatActor, CullSelectionBoxes) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(AGaussianSplatActor, KeepSelectionBoxes))
	{
		SynchronizeSelectionBoxes();
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(AGaussianSplatActor, bEnableCullSelectionBoxes) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(AGaussianSplatActor, bEnableKeepSelectionBoxes))
	{
		NotifySelectionBoxesChanged();
	}
}

void AGaussianSplatActor::PostEditUndo()
{
	Super::PostEditUndo();
	SynchronizeSelectionBoxes();
}
#endif

void AGaussianSplatActor::NotifySelectionBoxesChanged()
{
	if (GaussianSplatComponent)
	{
		GaussianSplatComponent->NotifySelectionBoxesChanged();
	}
}

UGaussianSplatSelectionBoxComponent* AGaussianSplatActor::CreateSelectionBox(
	EGaussianSplatSelectionBoxMode Mode,
	int32 Index)
{
	const TCHAR* BaseName = Mode == EGaussianSplatSelectionBoxMode::Keep
		? TEXT("KeepSelectionBox")
		: TEXT("CullSelectionBox");
	const FName ComponentName = MakeUniqueObjectName(this, UGaussianSplatSelectionBoxComponent::StaticClass(), BaseName);
	UGaussianSplatSelectionBoxComponent* NewBox = NewObject<UGaussianSplatSelectionBoxComponent>(
		this, ComponentName, RF_Transactional);
	if (!NewBox)
	{
		return nullptr;
	}

	NewBox->CreationMethod = EComponentCreationMethod::Instance;
	NewBox->SelectionBoxName = FName(*FString::Printf(
		TEXT("%s Box %d"),
		Mode == EGaussianSplatSelectionBoxMode::Keep ? TEXT("Keep") : TEXT("Cull"),
		Index + 1));
	NewBox->SetSelectionMode(Mode);
	NewBox->SetupAttachment(GaussianSplatComponent);

	FVector InitialCenter = FVector::ZeroVector;
	FVector InitialExtent(100.0);
	if (GaussianSplatComponent && GaussianSplatComponent->SplatAsset && GaussianSplatComponent->SplatAsset->IsValid())
	{
		const FBox AssetBounds = GaussianSplatComponent->SplatAsset->GetBounds();
		InitialCenter = AssetBounds.GetCenter();
		InitialExtent = AssetBounds.GetExtent() * 0.5;
		InitialExtent.X = FMath::Max(InitialExtent.X, 10.0);
		InitialExtent.Y = FMath::Max(InitialExtent.Y, 10.0);
		InitialExtent.Z = FMath::Max(InitialExtent.Z, 10.0);
	}

	NewBox->SetBoxExtent(InitialExtent);
	NewBox->SetRelativeLocation(InitialCenter);
	NewBox->SelectionBoxTransform = NewBox->GetRelativeTransform();
	AddInstanceComponent(NewBox);
	NewBox->RegisterComponent();
	return NewBox;
}

void AGaussianSplatActor::SynchronizeSelectionBoxes()
{
	auto SynchronizeArray = [this](
		TArray<TObjectPtr<UGaussianSplatSelectionBoxComponent>>& Boxes,
		EGaussianSplatSelectionBoxMode Mode)
	{
		if (Boxes.Num() > MaxSelectionBoxesPerMode)
		{
			Boxes.SetNum(MaxSelectionBoxesPerMode);
			UE_LOG(LogTemp, Warning, TEXT("GaussianSplat: Selection boxes are limited to %d entries per list."),
				MaxSelectionBoxesPerMode);
		}

		for (int32 Index = 0; Index < Boxes.Num(); ++Index)
		{
			UGaussianSplatSelectionBoxComponent* Box = Boxes[Index];
			if (!IsValid(Box))
			{
				Box = CreateSelectionBox(Mode, Index);
				Boxes[Index] = Box;
			}

			if (!IsValid(Box))
			{
				continue;
			}

			if (Box->SelectionBoxName.IsNone())
			{
				Box->SelectionBoxName = FName(*FString::Printf(
					TEXT("%s Box %d"),
					Mode == EGaussianSplatSelectionBoxMode::Keep ? TEXT("Keep") : TEXT("Cull"),
					Index + 1));
			}
			Box->SetSelectionMode(Mode);
			if (Box->GetAttachParent() != GaussianSplatComponent)
			{
				Box->AttachToComponent(GaussianSplatComponent, FAttachmentTransformRules::KeepRelativeTransform);
			}
			Box->SelectionBoxTransform = Box->GetRelativeTransform();
			if (!Box->IsRegistered())
			{
				Box->RegisterComponent();
			}
			if (!GetInstanceComponents().Contains(Box))
			{
				AddInstanceComponent(Box);
			}
		}
	};

	SynchronizeArray(CullSelectionBoxes, EGaussianSplatSelectionBoxMode::Cull);
	SynchronizeArray(KeepSelectionBoxes, EGaussianSplatSelectionBoxMode::Keep);

	TSet<UGaussianSplatSelectionBoxComponent*> ReferencedBoxes;
	for (UGaussianSplatSelectionBoxComponent* Box : CullSelectionBoxes)
	{
		if (IsValid(Box)) ReferencedBoxes.Add(Box);
	}
	for (UGaussianSplatSelectionBoxComponent* Box : KeepSelectionBoxes)
	{
		if (IsValid(Box)) ReferencedBoxes.Add(Box);
	}

	TArray<UGaussianSplatSelectionBoxComponent*> OrphanedBoxes;
	for (UActorComponent* InstanceComponent : GetInstanceComponents())
	{
		if (UGaussianSplatSelectionBoxComponent* Box = Cast<UGaussianSplatSelectionBoxComponent>(InstanceComponent))
		{
			if (!ReferencedBoxes.Contains(Box))
			{
				OrphanedBoxes.Add(Box);
			}
		}
	}
	for (UGaussianSplatSelectionBoxComponent* Box : OrphanedBoxes)
	{
		RemoveInstanceComponent(Box);
		Box->DestroyComponent();
	}

	NotifySelectionBoxesChanged();
}

void AGaussianSplatActor::RemoveInvalidSelectionBoxes()
{
	CullSelectionBoxes.RemoveAll([](const TObjectPtr<UGaussianSplatSelectionBoxComponent>& Box)
	{
		return !IsValid(Box);
	});
	KeepSelectionBoxes.RemoveAll([](const TObjectPtr<UGaussianSplatSelectionBoxComponent>& Box)
	{
		return !IsValid(Box);
	});
}
