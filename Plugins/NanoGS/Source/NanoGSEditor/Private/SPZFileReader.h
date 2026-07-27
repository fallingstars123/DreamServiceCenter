// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GaussianDataTypes.h"

/** Reader for Niantic legacy gzip-compressed SPZ files (versions 2 and 3). */
class FSPZFileReader
{
public:
	static bool IsValidSPZFile(const FString& FilePath);

	static bool ReadSPZFile(
		const FString& FilePath,
		TArray<FGaussianSplatData>& OutSplats,
		FString& OutError,
		int32* OutSHBands = nullptr);
};
