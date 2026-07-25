// Copyright Epic Games, Inc. All Rights Reserved.

#include "GaussianSplatAssetFactory.h"
#include "GaussianSplatAsset.h"
#include "PLYFileReader.h"
#include "COLMAPPointsReader.h"
#include "EditorFramework/AssetImportData.h"
#include "Misc/FeedbackContext.h"
#include "Misc/ScopedSlowTask.h"

UGaussianSplatAssetFactory::UGaussianSplatAssetFactory()
{
	bCreateNew = false;
	bEditorImport = true;
	bText = false;

	SupportedClass = UGaussianSplatAsset::StaticClass();

	Formats.Add(TEXT("ply;PLY Gaussian Splatting File"));
	Formats.Add(TEXT("bin;COLMAP Sparse Point Cloud (points3D.bin)"));
}

bool UGaussianSplatAssetFactory::FactoryCanImport(const FString& Filename)
{
	const FString Extension = FPaths::GetExtension(Filename);
	if (Extension.Equals(TEXT("ply"), ESearchCase::IgnoreCase))
	{
		return FPLYFileReader::IsValidPLYFile(Filename);
	}
	return Extension.Equals(TEXT("bin"), ESearchCase::IgnoreCase) &&
		FCOLMAPPointsReader::IsValidPointsFile(Filename);
}

UObject* UGaussianSplatAssetFactory::FactoryCreateFile(
	UClass* InClass,
	UObject* InParent,
	FName InName,
	EObjectFlags Flags,
	const FString& Filename,
	const TCHAR* Parms,
	FFeedbackContext* Warn,
	bool& bOutOperationCanceled)
{
	bOutOperationCanceled = false;

	const bool bIsCOLMAP = FPaths::GetExtension(Filename).Equals(TEXT("bin"), ESearchCase::IgnoreCase);
	UGaussianSplatAsset* NewAsset = bIsCOLMAP
		? ImportCOLMAPPointsFile(Filename, InParent, InName, Flags, nullptr)
		: ImportPLYFile(Filename, InParent, InName, Flags, nullptr);

	if (!NewAsset)
	{
		if (Warn)
		{
			Warn->Logf(ELogVerbosity::Error, TEXT("Failed to import Gaussian Splat from: %s"), *Filename);
		}
	}

	return NewAsset;
}

FText UGaussianSplatAssetFactory::GetDisplayName() const
{
	return FText::FromString(TEXT("Gaussian Splat Asset"));
}

bool UGaussianSplatAssetFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	UGaussianSplatAsset* Asset = Cast<UGaussianSplatAsset>(Obj);
	if (Asset && !Asset->SourceFilePath.IsEmpty())
	{
		OutFilenames.Add(Asset->SourceFilePath);
		return true;
	}
	return false;
}

void UGaussianSplatAssetFactory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
	UGaussianSplatAsset* Asset = Cast<UGaussianSplatAsset>(Obj);
	if (Asset && NewReimportPaths.Num() > 0)
	{
		Asset->SourceFilePath = NewReimportPaths[0];
	}
}

EReimportResult::Type UGaussianSplatAssetFactory::Reimport(UObject* Obj)
{
	UGaussianSplatAsset* Asset = Cast<UGaussianSplatAsset>(Obj);
	if (!Asset)
	{
		return EReimportResult::Failed;
	}

	if (Asset->SourceFilePath.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot reimport: source file path is empty"));
		return EReimportResult::Failed;
	}

	if (!FPaths::FileExists(Asset->SourceFilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot reimport: source file not found: %s"), *Asset->SourceFilePath);
		return EReimportResult::Failed;
	}

	// Preserve Nanite setting before reimport
	const bool bWasNaniteEnabled = Asset->IsNaniteEnabled();

	// Use the original quality level
	QualityLevel = Asset->ImportQuality;

	const bool bIsCOLMAP = FPaths::GetExtension(Asset->SourceFilePath).Equals(TEXT("bin"), ESearchCase::IgnoreCase);
	UGaussianSplatAsset* ReimportedAsset = bIsCOLMAP
		? ImportCOLMAPPointsFile(Asset->SourceFilePath, Asset->GetOuter(), Asset->GetFName(), Asset->GetFlags(), Asset)
		: ImportPLYFile(Asset->SourceFilePath, Asset->GetOuter(), Asset->GetFName(), Asset->GetFlags(), Asset);

	if (ReimportedAsset)
	{
		// If Nanite was enabled before reimport, rebuild the cluster hierarchy
		if (bWasNaniteEnabled && !bIsCOLMAP)
		{
			UE_LOG(LogTemp, Log, TEXT("Reimport: Rebuilding Nanite cluster hierarchy (was enabled before reimport)"));
			if (!ReimportedAsset->BuildNaniteClusterHierarchy())
			{
				UE_LOG(LogTemp, Warning, TEXT("Reimport: Failed to rebuild Nanite cluster hierarchy"));
			}
		}
		return EReimportResult::Succeeded;
	}

	return EReimportResult::Failed;
}

UGaussianSplatAsset* UGaussianSplatAssetFactory::ImportPLYFile(
	const FString& FilePath,
	UObject* InParent,
	FName InName,
	EObjectFlags Flags,
	UGaussianSplatAsset* ExistingAsset)
{
	FScopedSlowTask SlowTask(100.0f, FText::FromString(TEXT("Importing Gaussian Splat...")));
	SlowTask.MakeDialog(true);

	// Read PLY file
	SlowTask.EnterProgressFrame(30.0f, FText::FromString(TEXT("Reading PLY file...")));

	TArray<FGaussianSplatData> SplatData;
	FString ErrorMessage;
	int32 DetectedSHBands = 0;

	if (!FPLYFileReader::ReadPLYFile(FilePath, SplatData, ErrorMessage, &DetectedSHBands))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read PLY file: %s"), *ErrorMessage);
		return nullptr;
	}

	UE_LOG(LogTemp, Log, TEXT("Read %d splats from PLY file (SH bands: %d)"), SplatData.Num(), DetectedSHBands);

	return CreateAssetFromSplatData(
		FilePath, InParent, InName, Flags, SplatData, DetectedSHBands, false, ExistingAsset);
}

UGaussianSplatAsset* UGaussianSplatAssetFactory::ImportCOLMAPPointsFile(
	const FString& FilePath,
	UObject* InParent,
	FName InName,
	EObjectFlags Flags,
	UGaussianSplatAsset* ExistingAsset)
{
	FScopedSlowTask SlowTask(100.0f, FText::FromString(TEXT("Importing COLMAP Sparse Point Cloud...")));
	SlowTask.MakeDialog(true);
	SlowTask.EnterProgressFrame(35.0f, FText::FromString(TEXT("Reading points3D.bin...")));

	TArray<FGaussianSplatData> SplatData;
	FString ErrorMessage;
	if (!FCOLMAPPointsReader::ReadPointsFile(FilePath, SplatData, ErrorMessage))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read COLMAP points3D.bin: %s"), *ErrorMessage);
		return nullptr;
	}

	UE_LOG(LogTemp, Log, TEXT("Read %d sparse points from COLMAP points3D.bin"), SplatData.Num());
	SlowTask.EnterProgressFrame(65.0f, FText::FromString(TEXT("Creating point-cloud asset...")));
	return CreateAssetFromSplatData(
		FilePath, InParent, InName, Flags, SplatData, 0, true, ExistingAsset);
}

UGaussianSplatAsset* UGaussianSplatAssetFactory::CreateAssetFromSplatData(
	const FString& FilePath,
	UObject* InParent,
	FName InName,
	EObjectFlags Flags,
	TArray<FGaussianSplatData>& SplatData,
	int32 DetectedSHBands,
	bool bIsPointCloud,
	UGaussianSplatAsset* ExistingAsset)
{
	// Create or reuse asset

	UGaussianSplatAsset* Asset = ExistingAsset;
	if (!Asset)
	{
		Asset = NewObject<UGaussianSplatAsset>(InParent, UGaussianSplatAsset::StaticClass(), InName, Flags);
	}

	if (!Asset)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create Gaussian Splat asset"));
		return nullptr;
	}

	// Store source file path
	Asset->SourceFilePath = FilePath;
	Asset->bIsPointCloudAsset = bIsPointCloud;

	// Set the detected SH band count BEFORE initializing (CompressSH uses this)
	Asset->SHBands = DetectedSHBands;

	Asset->InitializeFromSplatData(SplatData, QualityLevel);

	// NO cluster hierarchy by default - user enables Nanite via Asset Actions > Nanite
	Asset->ClusterHierarchy.Reset();

	// Mark package dirty
	Asset->MarkPackageDirty();

	UE_LOG(LogTemp, Log, TEXT("Successfully imported %s asset: %d points, %lld bytes (Nanite disabled by default)"),
		bIsPointCloud ? TEXT("COLMAP point cloud") : TEXT("Gaussian Splat"),
		Asset->GetSplatCount(), Asset->GetMemoryUsage());

	return Asset;
}
