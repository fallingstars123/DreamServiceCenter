// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AutoUILayoutJson.h"
#include "CoreMinimal.h"
#include "Templates/Function.h"
#include "Misc/Optional.h"

class UTexture2D;

namespace AutoUIAiVision
{
	/**
	 * 异步调用配置的 AI 服务，完成后在主线程回调。
	 * bOk=true 时 Spec 为已校验的布局；Message 仍为可读摘要 + JSON 文本。
	 */
	void RequestLayoutJsonFromImage(
		UTexture2D* Texture,
		TFunction<void(bool bOk, FString Message, TOptional<FAutoUILayoutSpec> Spec)> OnCompleteOnGameThread);

	/** 使用已编码的 PNG 字节（如数学抠背景结果，含透明通道）请求布局 JSON。 */
	void RequestLayoutJsonFromPng(
		const TArray<uint8>& PngBytes,
		int32 ImageWidth,
		int32 ImageHeight,
		TFunction<void(bool bOk, FString Message, TOptional<FAutoUILayoutSpec> Spec)> OnCompleteOnGameThread);
}
