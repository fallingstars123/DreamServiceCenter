// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GaussianDataTypes.h"

/** Reader for COLMAP sparse reconstruction points3D.bin files. */
class FCOLMAPPointsReader
{
public:
	static bool IsValidPointsFile(const FString& FilePath);
	static bool ReadPointsFile(const FString& FilePath, TArray<FGaussianSplatData>& OutSplats, FString& OutError);
};
