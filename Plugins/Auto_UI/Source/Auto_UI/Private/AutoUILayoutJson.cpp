// Copyright Epic Games, Inc. All Rights Reserved.

#include "AutoUILayoutJson.h"

#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace AutoUILayoutJson_Private
{
	static bool ReadInt32(const TSharedPtr<FJsonObject>& Obj, const FString& Key, int32& OutValue, TArray<FString>& OutErrors, bool bRequired)
	{
		if (!Obj->HasField(Key))
		{
			if (bRequired)
			{
				OutErrors.Add(FString::Printf(TEXT("缺少字段: %s"), *Key));
				return false;
			}
			return true;
		}

		const TSharedPtr<FJsonValue> V = Obj->TryGetField(Key);
		double Num = 0.0;
		if (!V.IsValid() || !V->TryGetNumber(Num))
		{
			OutErrors.Add(FString::Printf(TEXT("字段 %s 不是数字"), *Key));
			return false;
		}

		OutValue = static_cast<int32>(FMath::RoundToInt(Num));
		return true;
	}

	static bool ReadString(const TSharedPtr<FJsonObject>& Obj, const FString& Key, FString& OutValue, TArray<FString>& OutErrors, bool bRequired)
	{
		if (!Obj->HasField(Key))
		{
			if (bRequired)
			{
				OutErrors.Add(FString::Printf(TEXT("缺少字段: %s"), *Key));
				return false;
			}
			return true;
		}

		const TSharedPtr<FJsonValue> V = Obj->TryGetField(Key);
		FString S;
		if (!V.IsValid() || !V->TryGetString(S))
		{
			OutErrors.Add(FString::Printf(TEXT("字段 %s 不是字符串"), *Key));
			return false;
		}

		OutValue = MoveTemp(S);
		return true;
	}
}

bool AutoUI_ParseAndValidateLayoutJson(
	const FString& JsonString,
	FAutoUILayoutSpec& OutSpec,
	TArray<FString>& OutErrors,
	const EAutoUILayoutJsonValidation Validation)
{
	const bool bPreview = (Validation == EAutoUILayoutJsonValidation::EditorPreview);
	OutSpec = FAutoUILayoutSpec();
	OutErrors.Reset();

	TSharedPtr<FJsonObject> Root;
	{
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
		TSharedPtr<FJsonValue> RootValue;
		if (!FJsonSerializer::Deserialize(Reader, RootValue) || !RootValue.IsValid())
		{
			OutErrors.Add(TEXT("JSON 解析失败（根节点无效）。"));
			return false;
		}

		const TSharedPtr<FJsonObject>* RootObj = nullptr;
		if (!RootValue->TryGetObject(RootObj) || !RootObj || !RootObj->IsValid())
		{
			OutErrors.Add(TEXT("JSON 根必须是对象。"));
			return false;
		}
		Root = *RootObj;
	}

	using namespace AutoUILayoutJson_Private;

	if (!ReadInt32(Root, TEXT("schema_version"), OutSpec.SchemaVersion, OutErrors, true))
	{
		return false;
	}

	if (OutSpec.SchemaVersion != 1)
	{
		OutErrors.Add(FString::Printf(TEXT("不支持的 schema_version=%d（当前仅支持 1）。"), OutSpec.SchemaVersion));
		return false;
	}

	ReadInt32(Root, TEXT("version"), OutSpec.Version, OutErrors, false);

	const TSharedPtr<FJsonObject>* DesignSizeObj = nullptr;
	if (!Root->TryGetObjectField(TEXT("design_size"), DesignSizeObj) || !DesignSizeObj || !DesignSizeObj->IsValid())
	{
		OutErrors.Add(TEXT("缺少对象字段 design_size { w, h }。"));
		return false;
	}

	if (!ReadInt32(*DesignSizeObj, TEXT("w"), OutSpec.DesignSize.X, OutErrors, true) ||
		!ReadInt32(*DesignSizeObj, TEXT("h"), OutSpec.DesignSize.Y, OutErrors, true))
	{
		return false;
	}

	if (OutSpec.DesignSize.X <= 0 || OutSpec.DesignSize.Y <= 0)
	{
		OutErrors.Add(TEXT("design_size 的 w/h 必须为正数。"));
		return false;
	}

	const TArray<TSharedPtr<FJsonValue>>* BlocksArray = nullptr;
	const TArray<TSharedPtr<FJsonValue>>* IconsArray = nullptr;
	const bool bHasBlocks = Root->TryGetArrayField(TEXT("blocks"), BlocksArray) && BlocksArray;
	const bool bHasIcons = Root->TryGetArrayField(TEXT("icons"), IconsArray) && IconsArray;

	const TArray<TSharedPtr<FJsonValue>>* ItemsArray = nullptr;
	FString ItemsKeyForErrors = TEXT("icons");

	if (bHasBlocks && BlocksArray->Num() > 0)
	{
		ItemsArray = BlocksArray;
		ItemsKeyForErrors = TEXT("blocks");
	}
	else if (bHasIcons && IconsArray->Num() > 0)
	{
		ItemsArray = IconsArray;
		ItemsKeyForErrors = TEXT("icons");
	}
	else
	{
		OutErrors.Add(TEXT("缺少非空的分块数组：请在 blocks 或 icons 中至少输出一项（每项 rect.(x,y) 为分块左上角）。"));
		return false;
	}

	TSet<FString> SeenIds;
	int32 NeededDesignW = OutSpec.DesignSize.X;
	int32 NeededDesignH = OutSpec.DesignSize.Y;

	for (int32 Index = 0; Index < ItemsArray->Num(); ++Index)
	{
		const TSharedPtr<FJsonValue>& ItemVal = (*ItemsArray)[Index];
		const TSharedPtr<FJsonObject>* ItemObj = nullptr;
		if (!ItemVal.IsValid() || !ItemVal->TryGetObject(ItemObj) || !ItemObj || !ItemObj->IsValid())
		{
			OutErrors.Add(FString::Printf(TEXT("%s[%d] 必须是对象。"), *ItemsKeyForErrors, Index));
			continue;
		}

		FAutoUILayoutIconEntry Entry;

		if (!ReadString(*ItemObj, TEXT("id"), Entry.Id, OutErrors, true))
		{
			continue;
		}

		if (Entry.Id.IsEmpty())
		{
			OutErrors.Add(FString::Printf(TEXT("%s[%d] 的 id 不能为空。"), *ItemsKeyForErrors, Index));
			continue;
		}

		if (SeenIds.Contains(Entry.Id))
		{
			OutErrors.Add(FString::Printf(TEXT("重复的分块 id: %s"), *Entry.Id));
			continue;
		}
		SeenIds.Add(Entry.Id);

		const TSharedPtr<FJsonObject>* RectObj = nullptr;
		if (!(*ItemObj)->TryGetObjectField(TEXT("rect"), RectObj) || !RectObj || !RectObj->IsValid())
		{
			OutErrors.Add(FString::Printf(TEXT("%s[%d] 缺少 rect { x,y,w,h }。"), *ItemsKeyForErrors, Index));
			continue;
		}

		if (!ReadInt32(*RectObj, TEXT("x"), Entry.X, OutErrors, true) ||
			!ReadInt32(*RectObj, TEXT("y"), Entry.Y, OutErrors, true) ||
			!ReadInt32(*RectObj, TEXT("w"), Entry.W, OutErrors, true) ||
			!ReadInt32(*RectObj, TEXT("h"), Entry.H, OutErrors, true))
		{
			continue;
		}

		if (Entry.W <= 0 || Entry.H <= 0)
		{
			OutErrors.Add(FString::Printf(TEXT("%s[%d] rect 的 w/h 必须为正。"), *ItemsKeyForErrors, Index));
			continue;
		}

		if (Entry.X < 0 || Entry.Y < 0)
		{
			OutErrors.Add(FString::Printf(TEXT("%s[%d] rect 的 x/y 不能为负。"), *ItemsKeyForErrors, Index));
			continue;
		}

		const int32 ReqW = Entry.X + Entry.W;
		const int32 ReqH = Entry.Y + Entry.H;
		NeededDesignW = FMath::Max(NeededDesignW, ReqW);
		NeededDesignH = FMath::Max(NeededDesignH, ReqH);

		if (!bPreview)
		{
			if (ReqW > OutSpec.DesignSize.X || ReqH > OutSpec.DesignSize.Y)
			{
				OutErrors.Add(FString::Printf(TEXT("%s[%d] rect 超出 design_size 范围。"), *ItemsKeyForErrors, Index));
				continue;
			}
		}

		ReadString(*ItemObj, TEXT("widget_type"), Entry.WidgetType, OutErrors, false);

		if ((*ItemObj)->HasField(TEXT("z_order")))
		{
			ReadInt32(*ItemObj, TEXT("z_order"), Entry.ZOrder, OutErrors, false);
		}

		OutSpec.Icons.Add(MoveTemp(Entry));
	}

	if (bPreview)
	{
		if (OutSpec.Icons.Num() == 0)
		{
			if (OutErrors.Num() == 0)
			{
				OutErrors.Add(TEXT("未能解析出任何有效分块。"));
			}
			return false;
		}

		if (NeededDesignW > OutSpec.DesignSize.X || NeededDesignH > OutSpec.DesignSize.Y)
		{
			const FIntPoint OldSize = OutSpec.DesignSize;
			OutSpec.DesignSize.X = NeededDesignW;
			OutSpec.DesignSize.Y = NeededDesignH;
			OutErrors.Add(FString::Printf(
				TEXT("提示：模型声明的 design_size 为 %dx%d，但分块 rect 需要至少 %dx%d；预览已自动扩展 design_size 以便标出红点/裁剪框。"),
				OldSize.X,
				OldSize.Y,
				OutSpec.DesignSize.X,
				OutSpec.DesignSize.Y));
		}

		return true;
	}

	if (OutErrors.Num() > 0)
	{
		return false;
	}

	return OutSpec.Icons.Num() > 0;
}

bool AutoUI_NormalizeLayoutSpecToTexture(
	FAutoUILayoutSpec& InOutSpec,
	const FIntPoint TextureSize,
	FString* OutNote)
{
	if (TextureSize.X <= 0 || TextureSize.Y <= 0 || InOutSpec.Icons.Num() == 0)
	{
		return false;
	}

	if (InOutSpec.DesignSize.X <= 0 || InOutSpec.DesignSize.Y <= 0)
	{
		InOutSpec.DesignSize = TextureSize;
		return false;
	}

	if (InOutSpec.DesignSize == TextureSize)
	{
		return false;
	}

	const FIntPoint OldDesign = InOutSpec.DesignSize;
	const float ScaleX = static_cast<float>(TextureSize.X) / static_cast<float>(OldDesign.X);
	const float ScaleY = static_cast<float>(TextureSize.Y) / static_cast<float>(OldDesign.Y);

	for (FAutoUILayoutIconEntry& Icon : InOutSpec.Icons)
	{
		Icon.X = FMath::RoundToInt(static_cast<float>(Icon.X) * ScaleX);
		Icon.Y = FMath::RoundToInt(static_cast<float>(Icon.Y) * ScaleY);
		Icon.W = FMath::Max(1, FMath::RoundToInt(static_cast<float>(Icon.W) * ScaleX));
		Icon.H = FMath::Max(1, FMath::RoundToInt(static_cast<float>(Icon.H) * ScaleY));

		Icon.X = FMath::Clamp(Icon.X, 0, TextureSize.X - 1);
		Icon.Y = FMath::Clamp(Icon.Y, 0, TextureSize.Y - 1);
		if (Icon.X + Icon.W > TextureSize.X)
		{
			Icon.W = TextureSize.X - Icon.X;
		}
		if (Icon.Y + Icon.H > TextureSize.Y)
		{
			Icon.H = TextureSize.Y - Icon.Y;
		}
	}

	InOutSpec.DesignSize = TextureSize;

	if (OutNote)
	{
		*OutNote = FString::Printf(
			TEXT("预览已按纹理像素将 design_size 从 %dx%d 归一化到 %dx%d（各分块 rect 已同比缩放）。"),
			OldDesign.X,
			OldDesign.Y,
			TextureSize.X,
			TextureSize.Y);
	}

	return true;
}

namespace AutoUILayoutJson_Private
{
	static bool DeserializeLayoutRoot(const FString& LayoutJson, TSharedPtr<FJsonObject>& OutRoot)
	{
		OutRoot.Reset();
		TSharedPtr<FJsonValue> RootValue;
		const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(LayoutJson);
		if (!FJsonSerializer::Deserialize(Reader, RootValue) || !RootValue.IsValid())
		{
			return false;
		}

		const TSharedPtr<FJsonObject>* RootObj = nullptr;
		if (!RootValue->TryGetObject(RootObj) || !RootObj || !RootObj->IsValid())
		{
			return false;
		}

		OutRoot = *RootObj;
		return true;
	}

	static FString SerializeLayoutRootPretty(const TSharedPtr<FJsonObject>& Root)
	{
		FString Out;
		const TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer =
			TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&Out);
		FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);
		return Out;
	}

	static bool TryReadDesignSize(const TSharedPtr<FJsonObject>& Root, FIntPoint& OutDesign)
	{
		const TSharedPtr<FJsonObject>* DesignObj = nullptr;
		if (!Root->TryGetObjectField(TEXT("design_size"), DesignObj) || !DesignObj || !DesignObj->IsValid())
		{
			return false;
		}

		double W = 0.0;
		double H = 0.0;
		if (!(*DesignObj)->TryGetNumberField(TEXT("w"), W) || !(*DesignObj)->TryGetNumberField(TEXT("h"), H))
		{
			return false;
		}

		OutDesign.X = static_cast<int32>(FMath::RoundToInt(W));
		OutDesign.Y = static_cast<int32>(FMath::RoundToInt(H));
		return OutDesign.X > 0 && OutDesign.Y > 0;
	}

	static int32 ScaleDesignInt(const int32 Value, const float Scale, const int32 MinValue = 0)
	{
		return FMath::Max(MinValue, FMath::RoundToInt(static_cast<float>(Value) * Scale));
	}

	static void TransformRectObject(const TSharedPtr<FJsonObject>& RectObj, const float ScaleX, const float ScaleY)
	{
		if (!RectObj.IsValid())
		{
			return;
		}

		double X = 0.0;
		double Y = 0.0;
		double W = 0.0;
		double H = 0.0;
		if (!RectObj->TryGetNumberField(TEXT("x"), X) || !RectObj->TryGetNumberField(TEXT("y"), Y) ||
			!RectObj->TryGetNumberField(TEXT("w"), W) || !RectObj->TryGetNumberField(TEXT("h"), H))
		{
			return;
		}

		RectObj->SetNumberField(TEXT("x"), ScaleDesignInt(static_cast<int32>(FMath::RoundToInt(X)), ScaleX));
		RectObj->SetNumberField(TEXT("y"), ScaleDesignInt(static_cast<int32>(FMath::RoundToInt(Y)), ScaleY));
		RectObj->SetNumberField(TEXT("w"), ScaleDesignInt(static_cast<int32>(FMath::RoundToInt(W)), ScaleX, 1));
		RectObj->SetNumberField(TEXT("h"), ScaleDesignInt(static_cast<int32>(FMath::RoundToInt(H)), ScaleY, 1));
	}

	static void TransformBlockItemObject(const TSharedPtr<FJsonObject>& ItemObj, const float ScaleX, const float ScaleY)
	{
		if (!ItemObj.IsValid())
		{
			return;
		}

		const TSharedPtr<FJsonObject>* RectObj = nullptr;
		if (ItemObj->TryGetObjectField(TEXT("rect"), RectObj) && RectObj && RectObj->IsValid())
		{
			TransformRectObject(*RectObj, ScaleX, ScaleY);
		}
	}

	static void TransformBlocksArray(const TSharedPtr<FJsonObject>& Root, const FString& ArrayKey, const float ScaleX, const float ScaleY)
	{
		const TArray<TSharedPtr<FJsonValue>>* Items = nullptr;
		if (!Root->TryGetArrayField(ArrayKey, Items) || !Items)
		{
			return;
		}

		for (const TSharedPtr<FJsonValue>& ItemVal : *Items)
		{
			const TSharedPtr<FJsonObject>* ItemObj = nullptr;
			if (ItemVal.IsValid() && ItemVal->TryGetObject(ItemObj) && ItemObj && ItemObj->IsValid())
			{
				TransformBlockItemObject(*ItemObj, ScaleX, ScaleY);
			}
		}
	}

	static TSharedPtr<FJsonObject> ConvertRootToPreviewViewportSpace(
		const TSharedPtr<FJsonObject>& SourceRoot,
		const FIntPoint ViewportSize,
		const FIntPoint SourceDesign)
	{
		const float ScaleX = static_cast<float>(ViewportSize.X) / static_cast<float>(SourceDesign.X);
		const float ScaleY = static_cast<float>(ViewportSize.Y) / static_cast<float>(SourceDesign.Y);

		const TSharedPtr<FJsonObject> ConvertedRoot = MakeShared<FJsonObject>(*SourceRoot);

		TransformBlocksArray(ConvertedRoot, TEXT("blocks"), ScaleX, ScaleY);
		TransformBlocksArray(ConvertedRoot, TEXT("icons"), ScaleX, ScaleY);

		const TSharedPtr<FJsonObject> ViewportObj = MakeShared<FJsonObject>();
		ViewportObj->SetNumberField(TEXT("w"), ViewportSize.X);
		ViewportObj->SetNumberField(TEXT("h"), ViewportSize.Y);

		const TSharedPtr<FJsonObject> DesignObj = MakeShared<FJsonObject>();
		DesignObj->SetNumberField(TEXT("w"), ViewportSize.X);
		DesignObj->SetNumberField(TEXT("h"), ViewportSize.Y);

		const TSharedPtr<FJsonObject> NewRoot = MakeShared<FJsonObject>();
		NewRoot->SetObjectField(TEXT("preview_viewport"), ViewportObj);
		NewRoot->SetStringField(TEXT("coordinate_space"), TEXT("preview_viewport"));

		for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : ConvertedRoot->Values)
		{
			if (Pair.Key == TEXT("preview_viewport") || Pair.Key == TEXT("coordinate_space") || Pair.Key == TEXT("design_size"))
			{
				continue;
			}
			NewRoot->SetField(Pair.Key, Pair.Value);
		}

		NewRoot->SetObjectField(TEXT("design_size"), DesignObj);
		return NewRoot;
	}
}

FString AutoUI_InjectPreviewViewportIntoLayoutJson(
	const FString& LayoutJson,
	const FIntPoint ViewportSize,
	const TOptional<FIntPoint> SourceDesignSize)
{
	if (ViewportSize.X <= 0 || ViewportSize.Y <= 0)
	{
		return LayoutJson;
	}

	TSharedPtr<FJsonObject> Root;
	if (!AutoUILayoutJson_Private::DeserializeLayoutRoot(LayoutJson, Root))
	{
		return LayoutJson;
	}

	FIntPoint SourceDesign = FIntPoint::ZeroValue;
	if (SourceDesignSize.IsSet() && SourceDesignSize.GetValue().X > 0 && SourceDesignSize.GetValue().Y > 0)
	{
		SourceDesign = SourceDesignSize.GetValue();
	}
	else if (!AutoUILayoutJson_Private::TryReadDesignSize(Root, SourceDesign))
	{
		return LayoutJson;
	}

	const TSharedPtr<FJsonObject> NewRoot =
		AutoUILayoutJson_Private::ConvertRootToPreviewViewportSpace(Root, ViewportSize, SourceDesign);
	return AutoUILayoutJson_Private::SerializeLayoutRootPretty(NewRoot);
}

FString AutoUI_StripPreviewViewportFromLayoutJson(const FString& LayoutJson)
{
	TSharedPtr<FJsonObject> Root;
	if (!AutoUILayoutJson_Private::DeserializeLayoutRoot(LayoutJson, Root))
	{
		return LayoutJson;
	}

	Root->RemoveField(TEXT("preview_viewport"));
	Root->RemoveField(TEXT("coordinate_space"));
	return AutoUILayoutJson_Private::SerializeLayoutRootPretty(Root);
}

FString AutoUI_SerializeLayoutSpecToJson(const FAutoUILayoutSpec& Spec)
{
	TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
	Root->SetNumberField(TEXT("schema_version"), Spec.SchemaVersion > 0 ? Spec.SchemaVersion : 1);
	Root->SetNumberField(TEXT("version"), Spec.Version > 0 ? Spec.Version : 1);

	TSharedPtr<FJsonObject> Design = MakeShared<FJsonObject>();
	Design->SetNumberField(TEXT("w"), Spec.DesignSize.X);
	Design->SetNumberField(TEXT("h"), Spec.DesignSize.Y);
	Root->SetObjectField(TEXT("design_size"), Design);

	TArray<TSharedPtr<FJsonValue>> Blocks;
	Blocks.Reserve(Spec.Icons.Num());
	for (const FAutoUILayoutIconEntry& Entry : Spec.Icons)
	{
		TSharedPtr<FJsonObject> Item = MakeShared<FJsonObject>();
		Item->SetStringField(TEXT("id"), Entry.Id);

		TSharedPtr<FJsonObject> Rect = MakeShared<FJsonObject>();
		Rect->SetNumberField(TEXT("x"), Entry.X);
		Rect->SetNumberField(TEXT("y"), Entry.Y);
		Rect->SetNumberField(TEXT("w"), Entry.W);
		Rect->SetNumberField(TEXT("h"), Entry.H);
		Item->SetObjectField(TEXT("rect"), Rect);

		if (!Entry.WidgetType.IsEmpty())
		{
			Item->SetStringField(TEXT("widget_type"), Entry.WidgetType);
		}
		if (Entry.ZOrder != 0)
		{
			Item->SetNumberField(TEXT("z_order"), Entry.ZOrder);
		}

		Blocks.Add(MakeShared<FJsonValueObject>(Item));
	}

	Root->SetArrayField(TEXT("blocks"), Blocks);
	return AutoUILayoutJson_Private::SerializeLayoutRootPretty(Root);
}
