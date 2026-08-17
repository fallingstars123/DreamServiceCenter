// Copyright Epic Games, Inc. All Rights Reserved.

#include "AutoUILayoutBlockMerge.h"

namespace AutoUILayoutBlockMerge_Private
{
	struct FComponentInfo
	{
		int32 MinX = 0;
		int32 MinY = 0;
		int32 MaxX = 0;
		int32 MaxY = 0;
		int32 Area = 0;
		bool bValid = false;

		void Include(const int32 X, const int32 Y)
		{
			if (!bValid)
			{
				MinX = MaxX = X;
				MinY = MaxY = Y;
				bValid = true;
			}
			else
			{
				MinX = FMath::Min(MinX, X);
				MinY = FMath::Min(MinY, Y);
				MaxX = FMath::Max(MaxX, X);
				MaxY = FMath::Max(MaxY, Y);
			}
			++Area;
		}
	};

	static bool IsForeground(const TArray<uint8>& Bgra, const int32 W, const int32 X, const int32 Y, const int32 AlphaThreshold)
	{
		const int64 Idx = (static_cast<int64>(Y) * W + X) * 4;
		return Bgra.IsValidIndex(Idx + 3) && Bgra[Idx + 3] > AlphaThreshold;
	}

	static void LabelForegroundComponents(
		const TArray<uint8>& Bgra,
		const int32 W,
		const int32 H,
		const FAutoUILayoutBlockMergeParams& Params,
		TArray<int32>& OutLabels,
		TArray<FComponentInfo>& OutComponents)
	{
		const int32 N = W * H;
		OutLabels.Init(0, N);
		OutComponents.Reset();

		const int32 AlphaThreshold = FMath::Clamp(Params.ForegroundAlphaThreshold, 1, 255);
		int32 NextLabel = 1;

		auto Index = [W](const int32 X, const int32 Y) { return Y * W + X; };

		for (int32 Y = 0; Y < H; ++Y)
		{
			for (int32 X = 0; X < W; ++X)
			{
				const int32 I = Index(X, Y);
				if (OutLabels[I] != 0 || !IsForeground(Bgra, W, X, Y, AlphaThreshold))
				{
					continue;
				}

				const int32 Label = NextLabel++;
				TArray<int32> Stack;
				Stack.Add(I);
				OutLabels[I] = Label;

				FComponentInfo Comp;

				while (Stack.Num() > 0)
				{
					const int32 Cur = Stack.Pop(EAllowShrinking::No);
					const int32 CX = Cur % W;
					const int32 CY = Cur / W;
					Comp.Include(CX, CY);

					const auto TryPush = [&](const int32 NX, const int32 NY)
					{
						if (NX < 0 || NY < 0 || NX >= W || NY >= H)
						{
							return;
						}
						const int32 NI = Index(NX, NY);
						if (OutLabels[NI] == 0 && IsForeground(Bgra, W, NX, NY, AlphaThreshold))
						{
							OutLabels[NI] = Label;
							Stack.Add(NI);
						}
					};

					TryPush(CX - 1, CY);
					TryPush(CX + 1, CY);
					TryPush(CX, CY - 1);
					TryPush(CX, CY + 1);

					if (Params.bEightConnected)
					{
						TryPush(CX - 1, CY - 1);
						TryPush(CX + 1, CY - 1);
						TryPush(CX - 1, CY + 1);
						TryPush(CX + 1, CY + 1);
					}
				}

				if (Comp.bValid)
				{
					while (OutComponents.Num() < Label)
					{
						OutComponents.AddDefaulted();
					}
					OutComponents[Label - 1] = Comp;
				}
			}
		}
	}

	static int32 FindDominantLabelInRect(
		const TArray<int32>& Labels,
		const int32 W,
		const int32 H,
		const FAutoUILayoutIconEntry& Icon,
		const TArray<uint8>& Bgra,
		const int32 AlphaThreshold)
	{
		const int32 X0 = FMath::Clamp(Icon.X, 0, W - 1);
		const int32 Y0 = FMath::Clamp(Icon.Y, 0, H - 1);
		const int32 X1 = FMath::Clamp(Icon.X + Icon.W - 1, 0, W - 1);
		const int32 Y1 = FMath::Clamp(Icon.Y + Icon.H - 1, 0, H - 1);

		TMap<int32, int32> Counts;
		for (int32 Y = Y0; Y <= Y1; ++Y)
		{
			for (int32 X = X0; X <= X1; ++X)
			{
				if (!IsForeground(Bgra, W, X, Y, AlphaThreshold))
				{
					continue;
				}
				const int32 Label = Labels[Y * W + X];
				if (Label > 0)
				{
					Counts.FindOrAdd(Label)++;
				}
			}
		}

		int32 BestLabel = 0;
		int32 BestCount = 0;
		for (const TPair<int32, int32>& Pair : Counts)
		{
			if (Pair.Value > BestCount)
			{
				BestCount = Pair.Value;
				BestLabel = Pair.Key;
			}
		}
		return BestLabel;
	}
}

int32 AutoUI_BuildLayoutSpecFromAlphaComponents(
	FAutoUILayoutSpec& OutSpec,
	const TArray<uint8>& Bgra,
	const int32 Width,
	const int32 Height,
	const FAutoUILayoutBlockMergeParams& Params,
	TArray<FString>* OutNotes)
{
	OutSpec = FAutoUILayoutSpec();
	OutSpec.SchemaVersion = 1;
	OutSpec.Version = 1;
	OutSpec.DesignSize = FIntPoint(Width, Height);

	if (Width <= 0 || Height <= 0)
	{
		if (OutNotes)
		{
			OutNotes->Add(TEXT("Alpha 分块失败：图像尺寸无效。"));
		}
		return 0;
	}

	const int64 Expected = static_cast<int64>(Width) * static_cast<int64>(Height) * 4;
	if (Bgra.Num() < Expected)
	{
		if (OutNotes)
		{
			OutNotes->Add(TEXT("Alpha 分块失败：像素缓冲尺寸不足。"));
		}
		return 0;
	}

	TArray<int32> Labels;
	TArray<AutoUILayoutBlockMerge_Private::FComponentInfo> Components;
	AutoUILayoutBlockMerge_Private::LabelForegroundComponents(Bgra, Width, Height, Params, Labels, Components);

	const int32 MinArea = FMath::Max(0, Params.MinComponentAreaPixels);
	int32 BlockIndex = 0;

	for (int32 LabelIdx = 0; LabelIdx < Components.Num(); ++LabelIdx)
	{
		const AutoUILayoutBlockMerge_Private::FComponentInfo& C = Components[LabelIdx];
		if (!C.bValid || C.Area < MinArea)
		{
			continue;
		}

		FAutoUILayoutIconEntry Entry;
		Entry.Id = FString::Printf(TEXT("block_%03d"), ++BlockIndex);
		Entry.WidgetType = TEXT("image");
		Entry.ZOrder = BlockIndex;
		Entry.X = C.MinX;
		Entry.Y = C.MinY;
		Entry.W = FMath::Max(1, C.MaxX - C.MinX + 1);
		Entry.H = FMath::Max(1, C.MaxY - C.MinY + 1);
		OutSpec.Icons.Add(MoveTemp(Entry));
	}

	if (OutNotes)
	{
		OutNotes->Add(FString::Printf(
			TEXT("Alpha 连通域分块：抠图前景（Alpha>%d）按 %s 连通共 %d 块（最小面积>=%d 像素）。"),
			FMath::Clamp(Params.ForegroundAlphaThreshold, 1, 255),
			Params.bEightConnected ? TEXT("8") : TEXT("4"),
			OutSpec.Icons.Num(),
			MinArea));
	}

	return OutSpec.Icons.Num();
}

void AutoUI_AttachAiMetadataToLayoutSpec(
	FAutoUILayoutSpec& InOutAlphaSpec,
	const FAutoUILayoutSpec& AiSpec,
	TArray<FString>* OutNotes)
{
	if (InOutAlphaSpec.Icons.Num() == 0 || AiSpec.Icons.Num() == 0)
	{
		return;
	}

	int32 Attached = 0;

	auto RectIntersectionArea = [](const FAutoUILayoutIconEntry& A, const FAutoUILayoutIconEntry& B) -> int64
	{
		const int32 X0 = FMath::Max(A.X, B.X);
		const int32 Y0 = FMath::Max(A.Y, B.Y);
		const int32 X1 = FMath::Min(A.X + A.W, B.X + B.W);
		const int32 Y1 = FMath::Min(A.Y + A.H, B.Y + B.H);
		if (X1 <= X0 || Y1 <= Y0)
		{
			return 0;
		}
		return static_cast<int64>(X1 - X0) * static_cast<int64>(Y1 - Y0);
	};

	for (FAutoUILayoutIconEntry& Block : InOutAlphaSpec.Icons)
	{
		int64 BestArea = 0;
		const FAutoUILayoutIconEntry* BestAi = nullptr;

		for (const FAutoUILayoutIconEntry& Ai : AiSpec.Icons)
		{
			const int64 Area = RectIntersectionArea(Block, Ai);
			if (Area > BestArea)
			{
				BestArea = Area;
				BestAi = &Ai;
			}
		}

		if (BestAi && BestArea > 0)
		{
			Block.Id = BestAi->Id;
			if (!BestAi->WidgetType.IsEmpty())
			{
				Block.WidgetType = BestAi->WidgetType;
			}
			if (BestAi->ZOrder != 0)
			{
				Block.ZOrder = BestAi->ZOrder;
			}
			++Attached;
		}
	}

	if (OutNotes)
	{
		OutNotes->Add(FString::Printf(
			TEXT("AI 语义挂载：%d/%d 块与 AI rect 有交集并已复制 id/widget_type（几何仍为 Alpha 包围盒）。"),
			Attached,
			InOutAlphaSpec.Icons.Num()));
	}
}

int32 AutoUI_MergeLayoutSpecByForegroundConnectivity(
	FAutoUILayoutSpec& InOutSpec,
	const TArray<uint8>& Bgra,
	const int32 Width,
	const int32 Height,
	const FAutoUILayoutBlockMergeParams& Params,
	TArray<FString>* OutNotes)
{
	const int32 BeforeCount = InOutSpec.Icons.Num();
	if (BeforeCount == 0 || Width <= 0 || Height <= 0)
	{
		return BeforeCount;
	}

	const int64 Expected = static_cast<int64>(Width) * static_cast<int64>(Height) * 4;
	if (Bgra.Num() < Expected)
	{
		if (OutNotes)
		{
			OutNotes->Add(TEXT("连通域合并跳过：像素缓冲尺寸不足。"));
		}
		return BeforeCount;
	}

	TArray<int32> Labels;
	TArray<AutoUILayoutBlockMerge_Private::FComponentInfo> Components;
	AutoUILayoutBlockMerge_Private::LabelForegroundComponents(Bgra, Width, Height, Params, Labels, Components);

	const int32 AlphaThreshold = FMath::Clamp(Params.ForegroundAlphaThreshold, 1, 255);
	const int32 MinArea = FMath::Max(0, Params.MinComponentAreaPixels);

	TSet<int32> ValidLabels;
	for (int32 LabelIdx = 0; LabelIdx < Components.Num(); ++LabelIdx)
	{
		const AutoUILayoutBlockMerge_Private::FComponentInfo& C = Components[LabelIdx];
		if (C.bValid && C.Area >= MinArea)
		{
			ValidLabels.Add(LabelIdx + 1);
		}
	}

	struct FGroup
	{
		FString Id;
		FString WidgetType;
		int32 ZOrder = 0;
		int32 Label = 0;
	};

	TMap<int32, FGroup> Groups;

	for (const FAutoUILayoutIconEntry& Icon : InOutSpec.Icons)
	{
		const int32 Label = AutoUILayoutBlockMerge_Private::FindDominantLabelInRect(
			Labels, Width, Height, Icon, Bgra, AlphaThreshold);
		if (Label <= 0 || !ValidLabels.Contains(Label))
		{
			continue;
		}

		if (FGroup* Existing = Groups.Find(Label))
		{
			if (Icon.ZOrder > Existing->ZOrder)
			{
				Existing->ZOrder = Icon.ZOrder;
			}
		}
		else
		{
			FGroup G;
			G.Id = Icon.Id;
			G.WidgetType = Icon.WidgetType;
			G.ZOrder = Icon.ZOrder;
			G.Label = Label;
			Groups.Add(Label, MoveTemp(G));
		}
	}

	TArray<FAutoUILayoutIconEntry> Merged;
	Merged.Reserve(Groups.Num());

	for (const TPair<int32, FGroup>& Pair : Groups)
	{
		const int32 Label = Pair.Key;
		const AutoUILayoutBlockMerge_Private::FComponentInfo& C = Components[Label - 1];
		if (!C.bValid)
		{
			continue;
		}

		FAutoUILayoutIconEntry Entry;
		Entry.Id = Pair.Value.Id;
		Entry.WidgetType = Pair.Value.WidgetType;
		Entry.ZOrder = Pair.Value.ZOrder;
		Entry.X = C.MinX;
		Entry.Y = C.MinY;
		Entry.W = FMath::Max(1, C.MaxX - C.MinX + 1);
		Entry.H = FMath::Max(1, C.MaxY - C.MinY + 1);
		Merged.Add(MoveTemp(Entry));
	}

	Merged.Sort([](const FAutoUILayoutIconEntry& A, const FAutoUILayoutIconEntry& B)
	{
		return A.ZOrder < B.ZOrder;
	});

	InOutSpec.Icons = MoveTemp(Merged);

	if (OutNotes)
	{
		OutNotes->Add(FString::Printf(
			TEXT("连通域合并：AI 输出 %d 项 → 按前景 %s 连通合并为 %d 项（无前景重叠的项已丢弃）。"),
			BeforeCount,
			Params.bEightConnected ? TEXT("8") : TEXT("4"),
			InOutSpec.Icons.Num()));
	}

	return BeforeCount;
}
